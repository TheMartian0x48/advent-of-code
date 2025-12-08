const std = @import("std");
const input = @embedFile("day-04.in");
// const input = @embedFile("example.in");

const Position = struct {
    row: usize,
    col: usize,
};

pub fn main() !void {
    var it = std.mem.tokenizeAny(u8, input, "\n");

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    var result: u64 = 0;

    var grid = try std.ArrayList(std.ArrayList(u8)).initCapacity(allocator, 256);
    defer grid.deinit(allocator);

    while (it.next()) |token| {
        var row = try std.ArrayList(u8).initCapacity(allocator, token.len);
        try row.appendSlice(allocator, token);
        try grid.append(allocator, row);
    }

    const dx = [8]i64{ 0, 0, -1, -1, -1, 1, 1, 1 };
    const dy = [8]i64{ -1, 1, -1, 0, 1, -1, 0, 1 };

    const rows = grid.items.len;
    const cols = grid.items[0].items.len;
    var has_rolled = true;

    var position_to_remove = std.ArrayList(Position).initCapacity(allocator, 256);
    defer position_to_remove.deinit(allocator);

    while (has_rolled) {
        for (0..rows) |r| {
            for (0..cols) |c| {
                if (grid.items[r].items[c] != '@') continue;
                var rolls: u32 = 0;
                for (0..8) |i| {
                    var new_row: i64 = @intCast(r);
                    new_row += dy[i];
                    var new_col: i64 = @intCast(c);
                    new_col += dx[i];
                    if (new_row >= 0 and new_row < rows and new_col >= 0 and new_col < cols) {
                        const rr: usize = @intCast(new_row);
                        const cc: usize = @intCast(new_col);
                        if (grid.items[rr].items[cc] == '@') {
                            rolls += 1;
                        }
                    }
                }
                if (rolls < 4) {
                    result += 1;
                    has_rolled = true;
                    const p = Position{
                        .row = r,
                        .col = c,
                    };
                    try position_to_remove.append(allocator, p);
                } else {
                    has_rolled = false;
                }
            }
        }
        while (position_to_remove.pop()) |p| {
            grid.items[p.row].items[p.col] = '.';
        }
    }
    for (0..rows) |row| {
        grid.items[row].deinit(allocator);
    }

    std.debug.print("{d}\n", .{result});
}
