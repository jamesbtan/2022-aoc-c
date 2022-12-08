const std = @import("std");
var gpa = std.heap.GeneralPurposeAllocator(.{}){};
const allr = gpa.allocator();

pub fn main() !void {
    const res = try parse();
    const map = res.al;
    defer map.deinit();
    const width = res.w;

    std.debug.print("Part 1: {}\n", .{try countVisible(map, width)});
    std.debug.print("Part 2: {}\n", .{maxScenic(map, width)});
    try benchmark(map, width);
}

const P = struct { al: std.ArrayList(u8), w: usize };

fn parse() !P {
    const file = try std.fs.cwd().openFile("input8", .{});
    defer file.close();
    var br = std.io.bufferedReader(file.reader());
    const reader = br.reader();

    var buf: [256]u8 = undefined;
    var map = std.ArrayList(u8).init(allr);
    var width: usize = undefined;
    while (try reader.readUntilDelimiterOrEof(&buf, '\n')) |line| {
        width = line.len;
        for (line) |ch| {
            try map.append(ch - '0');
        }
    }
    return P{ .al = map, .w = width };
}

fn countVisible(map: std.ArrayList(u8), width: usize) !u32 {
    const height = map.items.len / width;

    var scan = try allr.alloc(bool, map.items.len);
    defer allr.free(scan);
    std.mem.set(bool, scan, false);
    {
        var i: usize = 0;
        while (i < width) : (i += 1) {
            var block: u8 = map.items[i];
            scan[i] = true;
            var j: usize = 1;
            while (j < height) : (j += 1) {
                var curr = j * width + i;
                if (map.items[curr] > block) {
                    block = map.items[curr];
                    scan[curr] = true;
                }
            }
        }
    }
    {
        var i: usize = 0;
        while (i < width) : (i += 1) {
            var block: u8 = map.items[(height - 1) * width + i];
            scan[(height - 1) * width + i] = true;
            var j: usize = height - 1;
            while (j > 0) : (j -= 1) {
                var curr = (j - 1) * width + i;
                if (map.items[curr] > block) {
                    block = map.items[curr];
                    scan[curr] = true;
                }
            }
        }
    }
    {
        var j: usize = 0;
        while (j < height) : (j += 1) {
            var block: u8 = map.items[j * width];
            scan[j * width] = true;
            var i: usize = 1;
            while (i < width) : (i += 1) {
                var curr = j * width + i;
                if (map.items[curr] > block) {
                    block = map.items[curr];
                    scan[curr] = true;
                }
            }
        }
    }
    {
        var j: usize = 0;
        while (j < height) : (j += 1) {
            var block: u8 = map.items[j * width + width - 1];
            scan[j * width + width - 1] = true;
            var i: usize = width - 1;
            while (i > 0) : (i -= 1) {
                var curr = j * width + i - 1;
                if (map.items[curr] > block) {
                    block = map.items[curr];
                    scan[curr] = true;
                }
            }
        }
    }
    var count: u32 = 0;
    for (scan) |t| {
        if (t) {
            count += 1;
        }
    }
    return count;
}

fn maxScenic(map: std.ArrayList(u8), width: usize) usize {
    var max: usize = 0;
    for (map.items) |_, i| {
        const iscenic = calcScenic(map, width, i);
        max = std.math.max(max, iscenic);
    }
    return max;
}

fn calcScenic(map: std.ArrayList(u8), width: usize, ind: usize) usize {
    const height = map.items.len / width;
    const ind_w = ind % width;
    const ind_h = ind / width;
    var scenic: usize = 1;

    {
        var i = ind_w + 1;
        var s: usize = 0;
        while (i < width) : (i += 1) {
            s += 1;
            var curr = ind_h * width + i;
            if (map.items[curr] >= map.items[ind]) break;
        }
        scenic *= s;
    }
    {
        var i = ind_w;
        var s: usize = 0;
        while (i > 0) : (i -= 1) {
            s += 1;
            var curr = ind_h * width + i - 1;
            if (map.items[curr] >= map.items[ind]) break;
        }
        scenic *= s;
    }
    {
        var j = ind_h + 1;
        var s: usize = 0;
        while (j < height) : (j += 1) {
            s += 1;
            var curr = j * width + ind_w;
            if (map.items[curr] >= map.items[ind]) break;
        }
        scenic *= s;
    }
    {
        var j = ind_h;
        var s: usize = 0;
        while (j > 0) : (j -= 1) {
            s += 1;
            var curr = (j - 1) * width + ind_w;
            if (map.items[curr] >= map.items[ind]) break;
        }
        scenic *= s;
    }

    return scenic;
}

fn benchmark(map: std.ArrayList(u8), width: usize) !void {
    const warmup = 100;
    var i: u32 = 0;
    var time: u64 = 0;
    var timer = try std.time.Timer.start();
    while (i < 10000 + warmup) : (i += 1) {
        if (i >= warmup) timer.reset();
        _ = maxScenic(map, width);
        if (i >= warmup) time += timer.read();
    }
    time /= i - warmup;
    std.debug.print("{} ns/iter\n", .{ time });
}
