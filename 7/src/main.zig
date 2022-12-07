const std = @import("std");
var gpa = std.heap.GeneralPurposeAllocator(.{}){};
const alloc = gpa.allocator();

pub fn main() !void {
    var root: *Dir = Dir.create();
    { // parse
        const file = try std.fs.cwd().openFile("input7", .{});
        defer file.close();
        var fr = file.reader();
        var br = std.io.bufferedReader(fr);
        var reader = br.reader();

        var stack = std.ArrayList(*Dir).init(alloc);
        try stack.append(root);
        defer stack.deinit();
        var buf: [64]u8 = undefined;
        while (try reader.readUntilDelimiterOrEof(&buf, '\n')) |line| {
            var tok_i = std.mem.tokenize(u8, line, " ");
            if (tok_i.next()) |fTok| {
                switch (fTok[0]) {
                    '$' => {
                        const cmd = tok_i.next().?;
                        switch (cmd[0]) {
                            'c' => {
                                const arg = tok_i.next().?;
                                switch (arg[0]) {
                                    '/' => stack.shrinkRetainingCapacity(1),
                                    '.' => _ = stack.pop(),
                                    else => {
                                        const curr = stack.items[stack.items.len - 1];
                                        try stack.append(curr.dirs.get(arg).?);
                                    },
                                }
                            },
                            'l' => {},
                            else => unreachable,
                        }
                    },
                    'd' => {
                        var new_dir = Dir.create();
                        const name = try alloc.dupe(u8, tok_i.next().?);
                        const curr = stack.items[stack.items.len - 1];
                        try curr.dirs.put(name, new_dir);
                    },
                    else => {
                        const curr = stack.items[stack.items.len - 1];
                        curr.size += try std.fmt.parseInt(u32, fTok, 10);
                    },
                }
            }
        }
    }

    std.debug.print("{}\n", .{root.get_true_size()});
    std.debug.print("Part 1: {}\n", .{root.get_more_than(100000)});
    std.debug.print("Part 2: {}\n", .{root.get_min_more(root.size - 40000000).?});
}

const Dir = struct {
    dirs: std.StringHashMap(*Dir),
    size: u32 = 0,

    const Self = @This();

    fn create() *Dir {
        var d = alloc.create(Dir) catch unreachable;
        d.dirs = std.StringHashMap(*Dir).init(alloc);
        d.size = 0;
        return d;
    }

    fn get_true_size(self: *Self) u32 {
        var v_iter = self.dirs.valueIterator();
        while (v_iter.next()) |dir| {
            self.size += dir.*.get_true_size();
        }
        return self.size;
    }

    fn get_more_than(self: *Self, limit: u32) u32 {
        var res: u32 = if (self.size <= limit) self.size else 0;
        var v_iter = self.dirs.valueIterator();
        while (v_iter.next()) |dir| {
            res += dir.*.get_more_than(limit);
        }
        return res;
    }

    fn get_min_more(self: *Self, limit: u32) ?u32 {
        var res: ?u32 = if (self.size >= limit) self.size else null;
        var v_iter = self.dirs.valueIterator();
        while (v_iter.next()) |dir| {
            const ires = dir.*.get_min_more(limit);
            if (ires) |v_ires| {
                res = if (res) |v_res|
                    std.math.min(v_res, v_ires)
                else
                    v_ires;
            }
        }
        return res;
    }
};
