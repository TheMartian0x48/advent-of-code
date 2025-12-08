const std = @import("std");

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const args = try std.process.argsAlloc(allocator);
    defer std.process.argsFree(allocator, args);

    if (args.len < 2) {
        std.debug.print("Usage: {s} <input_file>\n", .{args[0]});
        return;
    }

    const file = try std.fs.cwd().openFile(args[1], .{});
    defer file.close();

    const content = try file.readToEndAlloc(allocator, 1024 * 1024);
    defer allocator.free(content);

    var iter = std.mem.splitSequence(u8, content, "\n");

    var dial: i32 = 50;
    var zero_count: i32 = 0;

    while (iter.next()) |line| {
        var trimmed = std.mem.trim(u8, line, " \r\t");
        if (trimmed.len == 0) continue;

        const dir = trimmed[0];
        const val_str = trimmed[1..];
        const val = try std.fmt.parseInt(i32, val_str, 10);

        if (dir == 'L') {
            dial -= val;
        } else if (dir == 'R') {
            dial += val;
        } else {
            std.debug.print("Invalid direction: {c}\n", .{dir});
            continue;
        }

        dial = @mod(dial, 100);

        if (dial == 0) {
            zero_count += 1;
        }
    }

    std.debug.print("{d}\n", .{zero_count});
}
const std = @import("std");

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const args = try std.process.argsAlloc(allocator);
    defer std.process.argsFree(allocator, args);

    if (args.len < 2) {
        std.debug.print("Usage: {s} <input_file>\n", .{args[0]});
        return;
    }

    const file = try std.fs.cwd().openFile(args[1], .{});
    defer file.close();

    const content = try file.readToEndAlloc(allocator, 1024 * 1024);
    defer allocator.free(content);

    var iter = std.mem.splitSequence(u8, content, "\n");

    var dial: i32 = 50;
    var zero_count: i32 = 0;

    while (iter.next()) |line| {
        var trimmed = std.mem.trim(u8, line, " \r\t");
        if (trimmed.len == 0) continue;

        const dir = trimmed[0];
        const val_str = trimmed[1..];
        const val = try std.fmt.parseInt(i32, val_str, 10);

        if (dir == 'L') {
            dial -= val;
        } else if (dir == 'R') {
            dial += val;
        } else {
            std.debug.print("Invalid direction: {c}\n", .{dir});
            continue;
        }

        dial = @mod(dial, 100);

        if (dial == 0) {
            zero_count += 1;
        }
    }

    std.debug.print("{d}\n", .{zero_count});
}
