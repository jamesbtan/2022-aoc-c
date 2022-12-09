const std = @import("std");
var gpa = std.heap.GeneralPurposeAllocator(.{}){};
const allr = gpa.allocator();

pub fn main() !void {
    const file = try std.fs.cwd().openFile("input9", .{});
    var br = std.io.bufferedReader(file.reader());
    const r = br.reader();

    var p = std.AutoHashMap(Pos, void).init(allr);
    var rope = Rope(10){};
    try p.put(rope.tail(), {});

    var buf: [16]u8 = undefined;
    while (try r.readUntilDelimiterOrEof(&buf, '\n')) |line| {
        const d = switch (line[0]) {
            'R' => Pos{ .x = 1, .y = 0 },
            'L' => Pos{ .x = -1, .y = 0 },
            'U' => Pos{ .x = 0, .y = 1 },
            'D' => Pos{ .x = 0, .y = -1 },
            else => unreachable,
        };
        var val = try std.fmt.parseInt(i32, line[2..], 10);
        //std.debug.print("====\n{} {}\n====\n", .{ d, val });
        while (val > 0) : (val -= 1) {
            rope.move(d);
            try p.put(rope.tail(), {});
        }
    }

    std.debug.print("{}\n", .{p.count()});
}

const Pos = struct {
    x: i32,
    y: i32,

    fn mul(pos: Pos, n: i32) Pos {
        return .{ .x = pos.x * n, .y = pos.y * n };
    }
    fn add(a: Pos, b: Pos) Pos {
        return .{ .x = a.x + b.x, .y = a.y + b.y };
    }
};

fn Rope(comptime N: usize) type {
    return struct {
        knots: [N]Pos = .{Pos{ .x = 0, .y = 0 }} ** N,

        const Self = @This();

        fn move(self: *Self, d: Pos) void {
            self.knots[0] = self.knots[0].add(d);
            for (self.knots[1..]) |*k, i| {
                const dist = self.knots[i].add(k.mul(-1));
                const touching = std.math.max(
                    std.math.absInt(dist.x) catch unreachable,
                    std.math.absInt(dist.y) catch unreachable,
                ) <= 1;
                if (!touching) {
                    const disp = Pos{
                        .x = std.math.sign(dist.x),
                        .y = std.math.sign(dist.y),
                    };
                    k.* = k.add(disp);
                }
            }
        }

        fn tail(self: Self) Pos {
            return self.knots[N - 1];
        }
    };
}
