import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score

# Assuming you have two signals, signal1 and signal2, and corresponding step values in a DataFrame
# You should replace this with your actual data source or load it from a file

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

df["timestamp(ms)"] = df["timestamp(ms)"].str.replace(",", ".")
df["timestamp(ms)"] = pd.to_numeric(df["timestamp(ms)"], errors="coerce")
df["timestamp(ms)"] = df["timestamp(ms)"] - df["timestamp(ms)"][0]
print(df["timestamp(ms)"].head())
for column in df.columns:
    df[column].ffill(inplace=True)

leg1 = df["s0"] + df["s1"]
leg2 = df["s2"] + df["s3"]
leg3 = df["s4"] + df["s5"]
leg4 = df["s6"] + df["s7"]
leg5 = df["s8"] + df["s9"]
leg6 = df["s10"] + df["s11"]  # calculate avarage for legs at every step
avg_leg = (leg1 + leg2 + leg3 + leg4 + leg5 + leg6) / 6

leg_group_1 = leg1 + leg4 + leg5
leg_group_2 = leg2 + leg3 + leg6

data_window = 30

mean1 = []
mean2 = []
peak_plus1 = []
peak_minus1 = []
peak_plus2 = []
peak_minus2 = []
slope1 = []
slope2 = []
time_since_last_step_change = []
time_to_next_step_change = []
for i in range(data_window, len(leg_group_1)):
    mean1.append(leg_group_1[i - data_window : i].mean())
    mean2.append(leg_group_2[i - data_window : i].mean())
    peak_plus1.append(leg_group_1[i - data_window : i].max())
    peak_minus1.append(leg_group_1[i - data_window : i].min())
    peak_plus2.append(leg_group_2[i - data_window : i].max())
    peak_minus2.append(leg_group_2[i - data_window : i].min())
    slope1.append((leg_group_1[i] - leg_group_1[i - data_window]) / data_window)
    slope2.append((leg_group_2[i] - leg_group_2[i - data_window]) / data_window)
    for j in range(i, len(leg_group_1)):
        if df["step"][j] != df["step"][i]:
            time_to_next_step_change.append(
                df["timestamp(ms)"][j] - df["timestamp(ms)"][i]
            )
            break
    if(len(time_to_next_step_change) != len(mean1)):
        break
    for j in range(i, 0, -1):
        if df["step"][j] != df["step"][i]:
            time_since_last_step_change.append(
                df["timestamp(ms)"][i] - df["timestamp(ms)"][j]
            )
            break

df_new = pd.DataFrame(
    {
        "mean1": mean1,
        "mean2": mean2,
        "peak_plus1": peak_plus1,
        "peak_minus1": peak_minus1,
        "peak_plus2": peak_plus2,
        "peak_minus2": peak_minus2,
        "slope1": slope1,
        "slope2": slope2,
        "time_since_last_step_change": time_since_last_step_change,
        "time_to_next_step_change": time_to_next_step_change,
    }
)

# Separate features (signals) and target (steps)
X = df_new[
    [
        "mean1",
        "mean2",
        "peak_plus1",
        "peak_minus1",
        "peak_plus2",
        "peak_minus2",
        "slope1",
        "slope2",
    ]
]
y = df_new[["time_since_last_step_change", "time_to_next_step_change"]]
# print(i for i, my_y in enumerate(y) if my_y != 0 and my_y != 1)
# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# Create a decision tree classifier
clf = DecisionTreeClassifier()

# Train the model on the training data
clf.fit(X_train, y_train)

# Make predictions on the test set
y_pred = clf.predict(X_test)

# Calculate and print the accuracy of the model
accuracy = accuracy_score(y_test, y_pred)
print(f"Accuracy: {accuracy:.2f}")
