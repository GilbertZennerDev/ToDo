"""
Usage: add tasks, view list of tasks
"""

import sys

def addTask(tasks, newtask):
	print(f"Task {newtask} added");
	tasks.append(newtask)
	return tasks
	
def deleteTask(tasks, deletetask):
	tasks = [task for task in tasks if deletetask not in task]
	print(f"Task .{deletetask}. deleted");
	return tasks

def listTasks(tasks):
	for task in tasks: print(task)
	
def saveTasks(tasks):
	try: open("todo.md", "w").write("\n".join(tasks))
	except Exception as e: print(e); return

def loadTasks():
	try: return open("todo.md", "r").read().splitlines()
	except Exception as e: print(e); return

def awaitCmd():
	tasks = ['milk']
	while 1:
		cmd = input("Usage: 'add milk' or 'list' or 'delete milk' or exit:\n")
		cmd = cmd.split(' ')
		if cmd[0] == "add": tasks = addTask(tasks, "".join(cmd[1:]))
		if cmd[0] == "delete": tasks = deleteTask(tasks, "".join(cmd[1:]))
		elif cmd[0] == "list": listTasks(tasks)
		elif cmd[0] == "save": saveTasks(tasks)
		elif cmd[0] == "load": tasks += loadTasks()
		elif cmd[0] == "exit": exit()

def	main():
	av = sys.argv
	ac = len(av)
	awaitCmd()

if __name__ == "__main__":main()
