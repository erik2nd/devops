#!/bin/bash

TELEGRAM_BOT_TOKEN=""
TELEGRAM_USER_ID=""

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="$1 stage $2"

curl -s -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
