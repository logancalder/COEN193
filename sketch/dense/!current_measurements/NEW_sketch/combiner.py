import os
import csv
import re
from datetime import datetime
from collections import defaultdict

# Directory containing all the CSV files
directory = 'papi_results'

# Event names in order of oldest to newest
event_order = ['false', 'master', 'close', 'spread']

# Function to extract the timestamp from the filename
def extract_timestamp(filename):
    try:
        match = re.search(r"(\d{4}-\d{2}-\d{2})-(\d{1,2})-(\d{1,2})-(\d{1,2})", filename)
        if not match:
            raise ValueError("No valid timestamp found in filename")

        date_part = match.group(1)
        time_part = "-".join(f"{int(part):02}" for part in match.groups()[1:])
        full_timestamp = f"{date_part}-{time_part}"
        return datetime.strptime(full_timestamp, "%Y-%m-%d-%H-%M-%S")
    except Exception as e:
        print(f"Error extracting timestamp from {filename}: {e}")
        return None

# List to hold files and their timestamps
files_with_timestamps = []

# Gather all relevant CSV files
for filename in os.listdir(directory):
    if filename.endswith('.csv'):
        timestamp = extract_timestamp(filename)
        if timestamp:
            files_with_timestamps.append((filename, timestamp))

# Sort files by timestamp (oldest first)
files_with_timestamps.sort(key=lambda x: x[1])

# Group files by thread configuration
threads = defaultdict(list)
for filename, timestamp in files_with_timestamps:
    thread_match = re.search(r"(\d+)_Create_Dense_Dist", filename)
    if thread_match:
        thread_num = int(thread_match.group(1))
        threads[thread_num].append((filename, timestamp))

# Ensure each thread has the correct number of events
for thread_num, files in threads.items():
    if len(files) != len(event_order):
        print(f"Warning: Thread {thread_num} has {len(files)} files, expected {len(event_order)}.")

# Process files and group data by metric
metrics_data = defaultdict(lambda: defaultdict(lambda: defaultdict(list)))
for thread_num, files in threads.items():
    files.sort(key=lambda x: x[1])  # Sort by timestamp
    for idx, (filename, _) in enumerate(files):
        if idx < len(event_order):
            event_name = event_order[idx]
            filepath = os.path.join(directory, filename)

            with open(filepath, mode='r') as file:
                reader = csv.reader(file)
                try:
                    header = next(reader)  # Skip the header
                    for row in reader:
                        metric, value = row
                        metrics_data[metric][event_name][thread_num].append(value)
                except StopIteration:
                    print(f"Skipping empty file: {filepath}")

# Write combined data to a new CSV file
output_filepath = f'{os.path.dirname(os.path.abspath(__file__))}_50000_1000_output.csv'
with open(output_filepath, mode='w', newline='') as file:
    writer = csv.writer(file)
    # Write header
    writer.writerow(['Metric'] + event_order)
    # Write data for each metric
    for metric, events in metrics_data.items():
        row = [metric]
        for event_name in event_order:
            # Gather all thread values for this event
            thread_values = [
                ",".join(events[event_name].get(thread_num, []))
                for thread_num in sorted(threads.keys())
            ]
            row.append(",".join(thread_values))
        writer.writerow(row)

print(f'Combined data written to {output_filepath}')
