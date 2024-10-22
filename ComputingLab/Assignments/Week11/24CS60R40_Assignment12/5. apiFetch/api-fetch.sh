#!/bin/bash


if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <search_word>"
    exit 1
fi

search_word=$1


if [ ! -f "api-links_5.txt" ]; then
    echo "File not found!"
    exit 1
fi


combined_json="combine.json"
echo "[" > $combined_json


first=true


echo "Fetching the data from URLs ..."


while IFS= read -r url; do

   
    response=$(curl -s "$url")

  
    if [ -z "$response" ]; then
        echo "No data received from $url"
        continue
    fi

  
    issue_id=$(echo "$response" | jq '.id // "null"')
    issue_number=$(echo "$response" | jq '.number // "null"')
    issue_title=$(echo "$response" | jq '.title // "null"')
    issue_user=$(echo "$response" | jq '.user.login // "null"')
    issue_labels=$(echo "$response" | jq '[.labels[]?.name // "null"]')

    if [ "$issue_id" == "null" ]; then
        echo "No valid issue data found at $url"
        
        continue
    fi

    
    if [ "$first" = true ]; then

        first=false
    else
        echo "," >> $combined_json
    fi


    echo "{
        \"id\": $issue_id,
        \"number\": $issue_number,
        \"title\": $issue_title,
        \"user\": $issue_user,
        \"labels\": $issue_labels
    }" >> $combined_json

done < "api-links_5.txt"


echo "]" >> $combined_json


echo "JSON file content:"
cat $combined_json


echo "Matching Results:"
jq --arg search "$search_word" '.[] | select(
    (.labels != null and (.labels[] | test($search; "i"))) or
    (.title | test($search; "i")) or
    (.user | test($search; "i"))
) | {id, title, user}' $combined_json
