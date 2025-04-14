#!/bin/bash

if (scp -o StrictHostKeyChecking=no src/cat/s21_cat src/grep/s21_grep erik@10.10.0.2:/home/erik);
then
    ssh -t erik@10.10.0.2 'sudo mv s21_cat s21_grep /usr/local/bin'
fi
    
if [ $? -ne 0 ]; then
  echo "Deployment failed"
  exit 1
else
  echo "Deployment succeeded"
fi

