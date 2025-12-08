const std = @import("std");
// const input = @embedFile("day-02.in");
const input = @embedFile("example.in");

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
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();
    var it = std.mem.tokenizeAny(u8, input, ",\n");

    var result: u64 = 0;

    while (it.next()) |token| {
        std.debug.print("{s}\n", .{token});
        if (token.len == 0) {
            break;
        }
        var t = std.mem.tokenizeScalar(u8, token, '-');
        const lb_str = t.next() orelse "";
        const ub_str = t.next() orelse "";
        const lb = try std.fmt.parseInt(u64, lb_str, 10);
        const ub = try std.fmt.parseInt(u64, ub_str, 10);

        var st = std.AutoHashMap(u64, bool).init(allocator);
        defer st.deinit();
        const dc = digitCount(ub);

        for (0..@divTrunc(dc, 2)) |i| {
            var start = try std.fmt.parseInt(u32, lb_str[0..(i + 1)], 10);
            const end = try std.fmt.parseInt(u32, ub_str[0..(i + 1)], 10);
            const tens = try std.math.powi(u64, 10, i + 1);

            while (start <= end) {
                var v: u64 = 0;
                const times = @divTrunc(dc, i + 1);
                for (0..times) |_| {
                    v = v * tens + start;
                }
                start += 1;
                if (v < lb) continue;
                if (v > ub) break;
                try st.put(v, true);
            }
        }

        // var kIter = st.keyIterator();
        // while (kIter.next()) |key| {
        //     result += @as(u64, *key);
        // }
        var iter = st.iterator();
        while (iter.next()) |entry| {
            result += entry.key_ptr.*; // or *entry.key_ptr
            std.debug.print("{d}\n", .{entry.key_ptr.*});
        }
        std.debug.print("--\n\n", .{});
    }
    std.debug.print("{d}\n", .{result});
}
