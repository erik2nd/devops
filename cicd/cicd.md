# Basic CI/CD

## Contents

1. [Setting up the gitlab-runner](#1-setting-up-the-gitlab-runner)
2. [Building](#2-building)
3. [Codestyle test](#3-codestyle-test)
4. [Integration tests](#4-integration-tests)
5. [Deployment stage](#5-deployment-stage)
6. [Notifications](#6-notifications)
7. [Results](#7-results)
 
<br>

## 1. Setting up the gitlab-runner

- **Task:** 
    - Download and install gitlab-runner on the virtual machine

- **Commands:**
    - `sudo apt-get update`
    - `sudo apt-get install -y curl build-essential clang-format`
    - `curl -LJ0 "https://s3.dualstack.us-east-1.amazonaws.com/gitlab-runner-downloads/latest/deb/gitlab-runner_amd64.deb"`
    - `sudo dpkg -i gitlab-runner_amd64.deb`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/1_1.png" alt="Downloading and installing gitlab-runner" title="Downloading and installing gitlab-runner" width="700"> </p>

    *** 
    <br>

- **Task:** 
    - Run gitlab-runner and register it for use in the current project

- **Commands:**
    - `sudo gitlab-runner start`
    - `sudo gitlab-runner register`

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/1_2.png" alt="Running gitlab-runner and registering it for use in the current project" title="Running gitlab-runner and registering it for use in the current project" width="700"> </p>

## 2. Building

- **Task:** 
    - Write a stage for CI to build applications from the C2_SimpleBashUtils project
        - In the gitlab-ci.yml file, add a stage to start the building via makefile from the C2 project
        - Save post-build files (artifacts) to a random directory with a 30-day retention period

- **Command:**
    - `touch .gitlab-ci.yml`    

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/2.png" alt="Build stage" title="Build stage" width="500"> </p>

## 3. Codestyle test

- **Task:** 
    - Write a stage for CI that runs a codestyle script (clang-format)
        - If the codefile didn't pass, fail the pipeline
        - In the pipeline, display the output of the clang-format utility

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/3.png" alt="Codestyle stage" title="Codestyle stage" width="500"> </p>

## 4. Integration tests

- **Task:** 
    - Write a stage for CI that runs your integration tests from the same project
        - Run this stage automatically only if the build and codestyle test passes successfully
        - If tests didn't pass, fail the pipeline
        - In the pipeline, display the output of the succeeded / failed integration tests

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/4.png" alt="Integration tests stage" title="Integration tests stage" width="500"> </p>

## 5. Deployment stage

- **Task:** 
    - Write a stage for CD that "deploys" the project on another virtual machine
        - Run this stage manually, if all the previous stages have passed successfully
        - In case of an error, fail the pipeline

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/5_1.png" alt="Deployment stage" title="Deployment stage" width="500"> </p>

    ***
    <br>

- **Task:** 
    - Write a bash script which copies the files received after the building (artifacts) into the /usr/local/bin directory of the second virtual machine using ssh and scp

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/5_2.png" alt="bash script which copies the files to the second machine" title="bash script which copies the files to the second machine" width="650"> </p>

- **Extra:**
    - To transfer files between two machines, it is needed to configure both machines' network adapters to an internal network and set a static IP address on each machine within the same subnet using following commands:
        - `sudo nano /etc/netplan/00-installer-config.yaml`
        - `sudo netplan apply`
    
    - <img src="images/5_3.png" alt="First machine network configuration" title="First machine network configuration" width="280"> <img src="images/5_4.png" alt="Second machine network configuration" title="Second machine network configuration" width="280"> 

    <br>

    - Following commands is needed to configure SSH access for the GitLab Runner so it can connect to a remote machine without a password prompt, using the provided SSH key:
        - `ssh-keygen` - generates an SSH key on the machine running the GitLab Runner
        - `sudo su` - switches to the root user
        - `nano /etc/gitlab-runner/config.toml` - goes to the runner settings and specify where to find the SSH agent, need to add the line environment = ["SSH_AUTH_SOCK=/tmp/ssh-agent"] in the file
        - `ssh-keyscan -H 10.10.0.2 >> /home/gitlab-runner/.ssh/known_hosts` - adds the remote host with the IP 10.10.0.2 to the known_hosts file for the gitlab-runner user
        - `cp /home/erik/.ssh/id_rsa /home/gitlab-runner/.ssh/` - copies the private SSH key id_rsa from the user erik to the .ssh directory of the gitlab-runner user, this allows the runner to use the key for SSH connections to a remote server
        - `cd /home/gitlab-runner/.ssh/` - changes the directory to .ssh under the gitlab-runner user
        - `chown gitlab-runner:gitlab-runner id_rsa known_hosts` - changes the ownership of the id_rsa and known_hosts files to the gitlab-runner user and group, this ensures that only the gitlab-runner user has access to these files, maintaining security when using SSH

    - <img src="images/5_5.png" alt="Configuring SSH access for the GitLab Runner" title="Configuring SSH access for the GitLab Runner" width="520">    

    <br>

    - To connect to the second machine without needing to enter a password, SSH key-based authentication must be configured. To do this, it is needed to copy the public key to the remote machine using following command: 
        - `ssh-copy-id erik@10.10.0.2`

    - <img src="images/5_6.png" alt="Adding SSH key to the second machine" title="Adding SSH key to the second machine" width="700"> 

    <br>

    - Written script copies files into a directory without user permissions, so it is needed to allow user to execute mv command with superuser rights without requiring a password. To do this, add the specified line to the /etc/sudoers file on the second machine using following command:
        - `sudo visudo`

    - <img src="images/5_7.png" alt="Allowing user to execute mv command without requiring a password" title="Allowing user to execute mv command without requiring a password" width="450"> 

## 6. Notifications

- **Task:** 
    - Set up notifications of successful/unsuccessful pipeline execution via bot named "[your nickname] DO6 CI/CD" in Telegram

- **Output:**     
    <p style="text-align: left; margin: 0;">
    <img src="images/6_1.png" alt="bash script, which call API Telegram and send a message to the user" title="bash script, which call API Telegram and send a message to the user" width="500"> </p>    
    <p style="text-align: left; margin: 0;">
    <img src="images/6_2.png" alt="Added notifications afterscript" title="Added notifications afterscript" width="500"> </p>     

## 7. Results    

- <img src="images/7_1.png" alt="Pipeline jobs succeded" title="Pipeline jobs succeded" width="700"> 
- <img src="images/7_2.png" alt="Telegram notifications" title="Telegram notifications" width="400"> 