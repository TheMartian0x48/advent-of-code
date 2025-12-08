const std = @import("std");
const input = @embedFile("day-02.in");
// const input = @embedFile("example.in");

fn digitCount(n: u64) u64 {
    if (n == 0) return 1;
    var count: u64 = 0;
    var temp_n = n;
    while (temp_n > 0) {
        temp_n /= 10;
        count += 1;
    }
    return count;
}

fn half(n: u64) !u64 {
    const d = digitCount(n);
    if (@mod(d, 2) == 1) {
        return try std.math.powi(u64, 10, @divTrunc(d, 2));
    }
    const v = try std.math.powi(u64, 10, @divTrunc(d, 2));

    return @divTrunc(n, v);
}

pub fn main() !void {
    var it = std.mem.tokenizeAny(u8, input, ",\n");

    var result: u64 = 0;

    while (it.next()) |token| {
        std.debug.print("{s}\n", .{token});
        if (token.len == 0) {
            break;
        }
        var t = std.mem.tokenizeScalar(u8, token, '-');
        const lb = try std.fmt.parseInt(u64, t.next() orelse "", 10);
        const ub = try std.fmt.parseInt(u64, t.next() orelse "", 10);

        var start = try half(lb);
        const end = try half(ub);

        while (start <= end) {
            const d = digitCount(start);

            var v = try std.math.powi(u64, 10, d);
            v = v * start + start;
            std.debug.print("{d} {d} ->{d}\n", .{ start, end, v });

            if (v > ub) break;

            start += 1;
            if (v < lb) continue;
            result += v;
        }
    }
    std.debug.print("{d}\n", .{result});
}
