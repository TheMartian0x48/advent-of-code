defmodule Common do
  def parse_from_file(f) do
    elements =
      File.stream!(f)
      |> Enum.map(fn x ->
        x
        |> String.split()
        |> Enum.map(&String.to_integer/1)
        |> List.to_tuple()
      end)

    left =
      elements
      |> Enum.map(fn x -> elem(x, 0) end)
      |> Enum.sort()

    right =
      elements
      |> Enum.map(fn x -> elem(x, 1) end)
      |> Enum.sort()

    {left, right}
  end
end

defmodule Day1 do
  def solve(f) do
    {left, right} = Common.parse_from_file(f)

    Enum.zip(left, right)
    |> Enum.map(fn {a, b} -> abs(a - b) end)
    |> List.foldl(0, fn a, b -> a + b end)
  end
end

defmodule Day2 do
  def solve(f) do
    {left, right} = Common.parse_from_file(f)
    occurencies = Enum.frequencies(right)
    Enum.reduce(left, 0, fn x, a -> a + x * Map.get(occurencies, x, 0) end)
  end
end
