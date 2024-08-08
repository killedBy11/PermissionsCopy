# Copying Permissions Between Users in Active Directory: A Necessity for Legacy File Trees
## Introduction
In the realm of managing file servers within Active Directory environments, best practices dictate the utilization of groups for permission assignments. This methodology ensures a streamlined, manageable, and scalable permissions architecture. However, the reality of operational environments often diverges from these best practices due to the evolution and expansion of file systems over time. Legacy file trees, characterized by their complex structures and individually assigned permissions, present a formidable challenge in maintaining and updating access controls. Recognizing the necessity to address these challenges, we have developed a C++ application designed to facilitate the copying of permissions from one user to another. This document outlines the rationale behind this development and its criticality for effective file server management in legacy systems.

## Background
Active Directory serves as the backbone for managing user identities and security policies within Windows environments. The assignment of permissions through groups is a foundational principle in ensuring that access control remains both efficient and secure. However, as organizations grow and evolve, so too do their file systems. Over time, what was once a meticulously organized file server can become a complex labyrinth of directories with individually assigned permissions. This scenario often arises from immediate business needs, project-specific requirements, or simply the lack of a comprehensive permissions management strategy.

## The Challenge of Legacy File Trees
Legacy file trees are characterized by their intricate and deeply nested structures, where permissions are frequently assigned on a per-user basis. This granularity, while flexible, leads to a significant management overhead and complicates the process of modifying access controls. In scenarios where an employee's role changes, or when reorganizing departments and their corresponding data access needs, the task of manually updating permissions is not only time-consuming but prone to errors.

Moreover, the inherent risk of disrupting business operations by inadvertently altering permissions necessitates a cautious approach. The complexity of these trees often deters organizations from undertaking the necessary reorganization of their file server permissions, leading to what can be described as a 'legacy lock-in'.

## The Solution: Automating Permission Copying
To address the challenges posed by legacy file trees, I developed a very simple C++ program that automates the process of copying permissions from one user to another. This tool is specifically designed to interact with Active Directory and file servers, offering a streamlined solution to a complex problem. The primary objectives of this application are:

- Efficiency: Significantly reduce the time and effort required to update permissions across complex file systems.
- Accuracy: Minimize the risk of human error by automating the permission copying process, ensuring that permissions are replicated exactly from one user to another.
- Flexibility: Provide administrators with the ability to quickly respond to organizational changes without the need to manually navigate and update individual file permissions.
## Rationale
While the principle of using groups for permission management remains the recommended approach, the reality of existing legacy systems cannot be ignored. The development of this tool stems from the recognition that, in certain contexts, a more flexible and immediate solution is required to maintain operational efficiency and security. By automating the copying of permissions, this application serves as a critical utility for administrators facing the daunting task of managing legacy file trees.

## Conclusion
The transition from individually assigned permissions to a group-based model is an ideal that many organizations strive for. However, the presence of legacy file trees in many environments necessitates innovative solutions to manage access controls effectively. Our C++ application represents a bridge between the current state of legacy systems and the ideal state of streamlined permissions management. By providing a means to efficiently and accurately copy permissions between users, we facilitate the ongoing maintenance and eventual reorganization of complex file systems, ensuring that access controls remain both manageable and secure.

# Manual

## Step one
The first step is to export the permissions from a root node using the "icacls" command. You can do it as follows: ```icacls <root> /save export.txt /t```. The ```<root>``` attribute should represent the root node in the file system. The ```/t``` parameter means that the export should take place recursively, on all subfolders and files of the ```<root>``` node.

## Step two
Identify the user SID that you want to copy from and the user SID of the destination user. This can be done using the command ```wmic useraccount get sid,name``` in PowerShell, prefferably run as an administrator in order to print Active Directory users.

## Step three
Launch the program and input the names for the input file, the output file and the source and target SIDs. The new text file should be created.

## Step four
Open the output file with Notepad++, right click on the bottom right where it says the format is UTF-8 and switch to UTF-16 LE, then save. This step is supposed to dissapear once the program will be able to output directly to UTF-16 LE.

## Step five
Import the permissions from the text file using the "icacls" command. You can do it as follows: ```icacls <parent> /restore <output>```. Beware:
- The ```<parent>``` directory should be the parent of the target file system node. For example, you exported the folder ```D:/lorem/ipsum``` and all its subfolders and files. At import, the path should be ```D:/lorem/```, because the ```icacls``` command will attempt to find the folder ```ipsum``` inside ```lorem```. Indicate its parent node, not itself like in the export.
- ```<output>``` should be the text file outputted by the program
