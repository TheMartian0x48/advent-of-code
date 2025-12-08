const std = @import("std");
const input = @embedFile("day-03.in");
// const input = @embedFile("example.in");

pub fn main() !void {
    var it = std.mem.tokenizeAny(u8, input, "\n");

    var result: u64 = 0;
    while (it.next()) |token| {
        var arr: [12]u8 = undefined;
        for (0..12) |i| {
            arr[i] = token[i];
        }
        for (12..token.len) |i| {
            const ch = token[i];
            var idx: usize = 12;
            for (0..11) |j| {
                if (arr[j] < arr[j + 1]) {
                    idx = j;
                    break;
                }
            }
            if (idx < 12) {
                for (idx..11) |j| {
                    arr[j] = arr[j + 1];
                }
                arr[11] = ch;
            } else {
                arr[11] = @max(arr[11], ch);
            }
        }
        var ans: u64 = 0;
        for (0..12) |i| {
            ans = ans * 10 + (arr[i] - '0');
        }
        result += ans;
    }
    std.debug.print("{d}\n", .{result});
}
