#!/bin/bash

TODO_FILE="todo_list.txt"


if [ "$#" -eq 0 ]; then
    echo "Usage:"
    echo "  $0 add \"<task_description>\" <priority>"
    echo "  $0 complete <task_id>"
    echo "  $0 show"
    exit 1
fi

operation="$1"


if [ "$operation" == "add" ]; then
    if [ "$#" -ne 3 ]; then
        echo "Incorrect number of arguments for add."
        echo "Usage:"
        echo "  $0 add \"<task_description>\" <priority>"
        exit 1
    fi

    description="$2"
    priority="$3"


    case "$priority" in
        high|medium|low) ;;
        *) 
            echo "Invalid priority level. Must be one of: high, medium, low."
            exit 1
            ;;
    esac


    task_id=$(($(wc -l < "$TODO_FILE") + 1))

  
    echo "$task_id | $description | $priority | incomplete" >> "$TODO_FILE"
    echo "Task added: $description (ID: $task_id)"
    exit 0
fi


if [ "$operation" == "complete" ]; then
    if [ "$#" -ne 2 ]; then
        echo "Incorrect number of arguments for complete."
        echo "Usage:"
        echo "  $0 complete <task_id>"
        exit 1
    fi

    task_id="$2"

 
    if ! grep -q "^$task_id |" "$TODO_FILE"; then
        echo "Task ID $task_id not found."
        exit 1
    fi


    sed -i.bak "/^$task_id |/ s/incomplete/complete/" "$TODO_FILE"
    echo "Task ID $task_id marked as complete."
    exit 0
fi

if [ "$operation" == "show" ]; then
    if [ "$#" -ne 1 ]; then
        echo "Incorrect number of arguments for show."
        echo "Usage:"
        echo "  $0 show"
        exit 1
    fi

    if [ ! -s "$TODO_FILE" ]; then
        echo "No tasks found."
        exit 0
    fi


    echo "Tasks:"
    awk -F '|' '{print $1 "|" $2 "|" $3 "|" $4}' "$TODO_FILE" | sort -t '|' -k3,3r -k4,4 | column -t -s '|'
    exit 0
fi

echo "Invalid operation type."
echo "Usage:"
echo "  $0 add \"<task_description>\" <priority>"
echo "  $0 complete <task_id>"
echo "  $0 show"
exit 1
