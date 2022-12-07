const std = @import("std");
var gpa = std.heap.GeneralPurposeAllocator(.{}){};
const alloc = gpa.allocator();

const Dir = struct {
    parent: ?*Dir,
    dirs: std.StringHashMap(*Dir),
    files: std.ArrayList(u32),
    size: u32 = 0,

    const Self = @This();

    fn create(parent: ?*Dir) *Dir {
        var d = alloc.create(Dir) catch unreachable;
        d.parent = parent;
        d.dirs = std.StringHashMap(*Dir).init(alloc);
        d.files = std.ArrayList(u32).init(alloc);
        d.size = 0;
        return d;
    }

    fn destroy(self: *Self) void {
        self.dirs.destroy();
        self.files.destroy();
        alloc.free(self);
    }

    fn get_root(self: *Self) *Self {
        var i_dir = self;
        while (i_dir.parent) |parent| {
            i_dir = parent;
        }
        return i_dir;
    }

    fn get_true_size(self: *Self) u32 {
        var v_iter = self.dirs.valueIterator();
        while (v_iter.next()) |dir| {
            self.size += dir.*.get_true_size();
        }
        for (self.files.items) |s| {
            self.size += s;
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
            var i_res = dir.*.get_min_more(limit);
            if (i_res) |vi_res| {
                if (res) |v_res| {
                    res = std.math.min(vi_res, v_res);
                } else {
                    res = vi_res;
                }
            }
        }
        return res;
    }
};

const Kind = enum {
    cmd,
    dir,
};

pub fn main() !void {
    const file = try std.fs.cwd().openFile("input7", .{});
    defer file.close();
    var fr = file.reader();
    var br = std.io.bufferedReader(fr);
    var reader = br.reader();

    var curr: ?*Dir = null;
    {
        var buf: [64]u8 = undefined;
        while (try reader.readUntilDelimiterOrEof(&buf, '\n')) |line| {
            var i: u32 = 0;
            var tok_i = std.mem.tokenize(u8, line, " ");
            var k: Kind = undefined;
            while (tok_i.next()) |tok| : (i += 1) {
                switch (i) {
                    0 => {
                        switch (tok[0]) {
                            '$' => k = .cmd,
                            'd' => k = .dir,
                            else => {
                                try curr.?.files.append(try std.fmt.parseInt(u32, tok, 10));
                                break;
                            },
                        }
                    },
                    1 => {
                        switch (k) {
                            .dir => {
                                var new_dir = Dir.create(curr);
                                const name = try alloc.alloc(u8, tok.len);
                                std.mem.copy(u8, name, tok);
                                try curr.?.dirs.put(name, new_dir);
                                break;
                            },
                            .cmd => {
                                switch (tok[0]) {
                                    'l' => {
                                        break;
                                    },
                                    'c' => {},
                                    else => unreachable,
                                }
                            },
                        }
                    },
                    else => {
                        curr = blk: {
                            if (tok[0] == '.') break :blk curr.?.parent;
                            if (curr) |c_dir| {
                                if (tok[0] == '/') {
                                    break :blk c_dir.get_root();
                                } else {
                                    break :blk c_dir.dirs.get(tok).?;
                                }
                            } else {
                                break :blk Dir.create(curr);
                            }
                        };
                    },
                }
            }
        }
    }
    curr = curr.?.get_root();
    std.debug.print("{}\n", .{curr.?.get_true_size()});
    std.debug.print("{}\n", .{curr.?.get_more_than(100000)});
    std.debug.print("{}\n", .{curr.?.get_min_more(curr.?.size - 40000000).?});
}
