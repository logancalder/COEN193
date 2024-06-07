import os
import csv
from collections import defaultdict

# Directory containing all the CSV files
directory = 'papi_results'

# Dictionary to hold combined data for each group
grouped_data = defaultdict(lambda: defaultdict(list))

# Iterate over all files in the directory
for filename in os.listdir(directory):
    if filename.endswith('.csv'):
        filepath = os.path.join(directory, filename)

        # Extract the group prefix (the part before the first underscore)
        group_prefix = filename.split('_')[0]

        with open(filepath, mode='r') as file:
            reader = csv.reader(file)
            try:
                header = next(reader)  # Attempt to read the header
                for row in reader:
                    event_name, value = row
                    grouped_data[group_prefix][event_name].append(value)
            except StopIteration:
                # Handle empty file
                print(f'Skipping empty file: {filepath}')
                continue

# Prepare the output data
output_data = defaultdict(list)
for group, events in grouped_data.items():
    for event_name, values in events.items():
        combined_values = ",".join(values)
        output_data[event_name].append(combined_values)

# Write the combined data to a new CSV file
output_filepath = 'combined_output.csv'
with open(output_filepath, mode='w', newline='') as file:
    writer = csv.writer(file)
    # Writing header
    writer.writerow(['Event Name'] + list(grouped_data.keys()))
    # Writing data
    for event_name, values in output_data.items():
        writer.writerow([event_name] + values)

print(f'Combined data written to {output_filepath}')
