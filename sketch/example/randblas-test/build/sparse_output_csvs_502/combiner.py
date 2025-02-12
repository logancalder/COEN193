import csv
import os
from collections import defaultdict

def process_csv_by_metric(input_file, event):
    # Read the CSV file
    with open(input_file, 'r') as file:
        reader = csv.reader(file)
        headers = next(reader)  # Extract headers
        data = list(reader)
    
    # Initialize containers for metrics
    metrics = {header: [] for header in headers if header != "Threads"}
    
    # Populate metrics with data from the file
    for row in data:
        for idx, header in enumerate(headers):
            if header != "Threads":
                metrics[header].append(row[idx])
    
    # Return data structured by metric and event
    return {metric: {event: values} for metric, values in metrics.items()}

def consolidate_metrics(metrics, consolidated_data, all_events):
    # Merge metrics data into consolidated_data
    for metric, events in metrics.items():
        if metric not in consolidated_data:
            consolidated_data[metric] = defaultdict(list)
        for event, values in events.items():
            consolidated_data[metric][event].extend(values)
    
    # Ensure every event is represented, even if empty
    for metric in consolidated_data.keys():
        for event in all_events:
            if event not in consolidated_data[metric]:
                consolidated_data[metric][event] = []

def write_grouped_metrics(consolidated_data, output_dir="output"):
    os.makedirs(output_dir, exist_ok=True)
    
    # Write each metric to its corresponding CSV file
    for metric, event_data in consolidated_data.items():
        output_file = os.path.join(output_dir, f"{metric}.csv")
        
        # Prepare the header row
        events = ["false", "true", "master", "close", "spread"]
        with open(output_file, 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(["Metric"] + events)
            
            # Write data rows
            row = [metric]
            for event in events:
                row.append(",".join(event_data[event]))
            writer.writerow(row)

# Main script for batch processing
def process_all_csvs(input_files):
    all_events = ["false", "true", "master", "close", "spread"]
    consolidated_data = {}
    
    for input_file in input_files:
        # Extract event from filename (e.g., 'close' from 'runtime_close.csv')
        event = os.path.splitext(os.path.basename(input_file))[0].split('_')[-1]
        
        # Process the CSV and merge its data
        metrics = process_csv_by_metric(input_file, event)
        consolidate_metrics(metrics, consolidated_data, all_events)
    
    # Write all grouped metrics to their respective files
    write_grouped_metrics(consolidated_data)

# Example usage
input_files = ["runtime_close.csv", "runtime_false.csv", "runtime_master.csv", "runtime_true.csv", "runtime_spread.csv"]
process_all_csvs(input_files)
