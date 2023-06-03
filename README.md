# git_clone

## Commands

- git init

creates a .git_clone folder with all the necessary files to start using git_clone

- git add %s < file_path>

adds a file to the open commit

- git commit %s %s <-m || --message> < message>

for each file in open commit, registers its content

closes the commit by adding its message

creates a new open commit

- git log %s <-c || --content || NULL>

shows all commits and its file paths

if -c or --content flags are passed, shows the content of each file

- git show %d < commit_id>

shows the content of a commit with given id

- git checkout %d < commit_id>

for each file in commit with given id, reverts its state to the state registered on the commit