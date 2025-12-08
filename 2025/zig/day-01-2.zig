const std = @import("std");
const input = @embedFile("day-01.in");

pub fn main() !void {
    var it = std.mem.tokenizeScalar(u8, input, '\n');

    var dial: i32 = 50;
    var zero_count: i32 = 0;
    while (it.next()) |token| {
        const step = try std.fmt.parseInt(u32, token[1..], 10);
        if (token[0] == 'L') {
            for (0..step) |_| {
                dial = dial - 1;
                if (dial == 0) {
                    zero_count += 1;
                }
                if (dial == -1) {
                    dial = 99;
                }
            }
        } else {
            for (0..step) |_| {
                dial = dial + 1;
                if (dial == 100) {
                    dial = 0;
                    zero_count += 1;
                }
            }
        }
    }
    std.debug.print("{d}\n", .{zero_count});
}
