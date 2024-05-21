import matplotlib.pyplot as plt

for file in [
    "output_5.txt",
]:
    with open(file, "r") as f:
        lines = f.readlines()

        x = []
        y = []
        for line in lines:
            y.append(float(line.split(" ")[0]))
            x.append(float(line.split(" ")[1]))

        plt.plot(x, y)

plt.xlabel("Tile Size")
plt.ylabel("Execution Time in seconds")
plt.title("Execution Time vs Tile Size (string length 500)")
plt.legend(
    [
    ]
)

plt.show()