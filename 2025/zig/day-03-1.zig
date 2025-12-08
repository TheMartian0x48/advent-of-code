const std = @import("std");
const input = @embedFile("day-03.in");
// const input = @embedFile("example.in");

pub fn main() !void {
    var it = std.mem.tokenizeAny(u8, input, "\n");

    var result: u64 = 0;
    while (it.next()) |token| {
        if (token.len == 1) {
            result += token[0] - '0';
            continue;
        }

        var mx: u64 = token[0];
        var ans: u64 = 0;

        for (1..token.len) |i| {
            const temp = (mx - '0') * 10 + (token[i] - '0');
            ans = @max(ans, temp);
            mx = @max(mx, token[i]);
        }
        result += ans;
    }
    std.debug.print("{d}\n", .{result});
}
