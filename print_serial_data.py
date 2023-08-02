import matplotlib.pyplot as plt
import pandas as pd

# steps = {"name": [], "start": [], "end": []}
# cnt = 0
# steps["start"].append(0)
# with open("cleared_data.csv", "w") as nf:
#     with open("data.csv", "r") as f:
#         for line in f.readlines():
#             if ";" in line:
#                 cnt += 1
#                 nf.write(line)
#             elif "LEG" in line:
#                 steps["name"].append(line[:-1])
#                 steps["start"].append(cnt + 1)
#                 steps["end"].append(cnt)

# df = pd.read_csv(
#     "data.csv",
#     names=[

#         "s0",
#         "s1",
#         "s2",
#         "s3",
#         "s4",
#         "s5",
#         "s6",
#         "s7",
#         "s8",
#         "s9",
#         "s10",
#         "s11",
#         "end",
#     ],
#     sep=";",
# )

df = pd.read_csv(
    # "teleplot_2023-6-31_23-32.csv",
    # "teleplot_2023-7-1_1-46.csv",
    "teleplot_2023-7-1_2-1.csv",
    # names=[
    #     "time",
    #     "s0",
    #     "s1",
    #     "s2",
    #     "s3",
    #     "s4",
    #     "s5",
    #     "s6",
    #     "s7",
    #     "s8",
    #     "s9",
    #     "s10",
    #     "s11",
    #     "end",
    # ],
    header=0,
    sep=",",
)
df = df.drop(columns=["Unnamed: 14"])
print(df["timestamp(ms)"].head())
df["timestamp(ms)"] = df["timestamp(ms)"].str.replace(",", ".")
df["timestamp(ms)"] = pd.to_numeric(df["timestamp(ms)"], errors="coerce")
df["timestamp(ms)"] = df["timestamp(ms)"] - df["timestamp(ms)"][0]

for column in df.columns:
    df[column].ffill(inplace=True)

print(df.head())
plt.figure(1)
plt.plot(df["timestamp(ms)"], df["s0"], label="s0")
plt.plot(df["timestamp(ms)"], df["s1"], label="s1")
plt.plot(df["timestamp(ms)"], df["s2"], label="s2")
plt.plot(df["timestamp(ms)"], df["s3"], label="s3")
# plt.plot(df["timestamp(ms)"], df["s4"], label="s4")
# plt.plot(df["timestamp(ms)"], df["s5"], label="s5")
# plt.plot(df["timestamp(ms)"], df["s6"], label="s6")
# plt.plot(df["timestamp(ms)"], df["s7"], label="s7")
plt.plot(df["timestamp(ms)"], df["s8"], label="s8")
plt.plot(df["timestamp(ms)"], df["s9"], label="s9")
plt.plot(df["timestamp(ms)"], df["s10"], label="s10")
plt.plot(df["timestamp(ms)"], df["s11"], label="s11")
plt.plot(df["timestamp(ms)"], df["step"] * 300, label="step")
plt.legend()
plt.grid()

# calculate avarage for sensors at every step
df["avg0-5"] = df[
    ["s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11"]
].mean(axis=1)

plt.figure(2)
plt.plot(df["timestamp(ms)"], df["s0"] - df["avg0-5"], label="s0")
plt.plot(df["timestamp(ms)"], df["s1"] - df["avg0-5"], label="s1")
plt.plot(df["timestamp(ms)"], df["s2"] - df["avg0-5"], label="s2")
plt.plot(df["timestamp(ms)"], df["s3"] - df["avg0-5"], label="s3")
plt.plot(df["timestamp(ms)"], df["step"] * 50, label="step")
# plt.plot(df["timestamp(ms)"], df["s4"] - df["avg0-5"], label="s4")
# plt.plot(df["timestamp(ms)"], df["s5"] - df["avg0-5"], label="s5")
plt.legend()
plt.grid()
leg1 = df["s0"] + df["s1"]
leg2 = df["s2"] + df["s3"]
leg3 = df["s4"] + df["s5"]
leg4 = df["s6"] + df["s7"]
leg5 = df["s8"] + df["s9"]
leg6 = df["s10"] + df["s11"]  # calculate avarage for legs at every step
avg_leg = (leg1 + leg2 + leg3 + leg4 + leg5 + leg6) / 6

plt.figure(3)
plt.plot(df["timestamp(ms)"], leg1 - avg_leg, label="leg 1")
plt.plot(df["timestamp(ms)"], leg2 - avg_leg, label="leg 2")
plt.plot(df["timestamp(ms)"], leg3 - avg_leg, label="leg 3")
plt.plot(df["timestamp(ms)"], leg4 - avg_leg, label="leg 4")
plt.plot(df["timestamp(ms)"], leg5 - avg_leg, label="leg 5")
plt.plot(df["timestamp(ms)"], leg6 - avg_leg, label="leg 6")

plt.plot(df["timestamp(ms)"], df["step"] * 50, label="step")

plt.legend()
plt.grid()


leg_group_1 = leg1 + leg4 + leg5
leg_group_2 = leg2 + leg3 + leg6

plt.figure(4)
plt.plot(df["timestamp(ms)"], leg_group_1, label="leg group 1")
plt.plot(df["timestamp(ms)"], leg_group_2, label="leg group 2")
plt.plot(df["timestamp(ms)"], df["step"] * 1800, label="step")

plt.legend()
plt.grid()

# df = df.drop(columns=["empty"])
# target = {"name": [], "time": []}

# for (i, row) in df.iterrows():
#     if "LEG" in row["end"]:
#         target["name"].append(row["end"])
#         target["time"].append(i)

# print(df.head())
# time = df.index.values
# max = len(target["name"]) - 1
# # get data for each step
# # for i in range(2, 5):
# # print(len(target["name"]))
# start = target["time"][1]
# end = target["time"][max]
# df_step = df.iloc[start:end]
# time_step = time[start:end]
# for leg in range(0, 6):
#     plt.figure(leg)
#     match (leg):
#         case 0:
#             plt.plot(time_step, df_step["s0"], label="s0")
#             plt.plot(time_step, df_step["s1"], label="s1")
#         case 1:
#             plt.plot(time_step, df_step["s2"], label="s2")
#             plt.plot(time_step, df_step["s3"], label="s3")
#         case 2:
#             plt.plot(time_step, df_step["s4"], label="s4")
#             plt.plot(time_step, df_step["s5"], label="s5")
#         case 3:
#             plt.plot(time_step, df_step["s6"], label="s6")
#             plt.plot(time_step, df_step["s7"], label="s7")
#         case 4:
#             plt.plot(time_step, df_step["s8"], label="s8")
#             plt.plot(time_step, df_step["s9"], label="s9")
#         case 5:
#             plt.plot(time_step, df_step["s10"], label="s10")
#             plt.plot(time_step, df_step["s11"], label="s11")
#     plt.xlabel("time")
#     plt.ylabel("sensor value")
#     plt.title(f"LEG: {leg}\nSensor values for step: {target['name'][2]}")
#     for i in range(1, max):
#         if "LIFT" in target["name"][i]:
#             plt.axvline(x=time[target["time"][i]], color="g", linestyle="--")
#         else:
#             plt.axvline(x=time[target["time"][i]], color="r", linestyle="--")
#     plt.legend()

plt.show()
