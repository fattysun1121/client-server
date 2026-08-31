# Client/Server Learning Project

**Target platform:** Ubuntu Desktop 24.04.4 LTS ARM64 on UTM  

> This is a living project specification. Items marked **TBD** have not been
> decided.

## 1. Project Purpose

Build a learning project in C++ that explores the client-server separation. 
The confirmed baseline consists of one local client and one local
server on the same Linux computer, with two-way communication between them.

The project is also intended to develop:

- Linux command-line skills (file permission, basic commands)
- C++ build (cmake), resource-management, and debugging skills
- Socket programming skills (understanding of TCP, IP, and UDP)
- Multithreading and synchronization skills
- PostgreSQL and DB skills (CRUD, pqxx)
- tmux and bash script skills

The exact role of sessions, multithreading, and PostgreSQL is not yet
finalized.

## 2. Confirmed Scope

### 2.1 System boundary

- The entire program runs on one Linux computer.
- The baseline contains one client program.
- The baseline contains one server program.
- The client and server are separate processes.
- The client and server exchange data in both directions.

### 2.2 Technical learning constraints

- C++ is the implementation language
- Linux is the target operating system
- Client-server socket programming must be learned and demonstrated
- Multithreading must be learned and used; its responsibility is **TBD**
- PostgreSQL and DB must be learned
- cmake must be used to build the project
- tmux and bash scripts are used to develop and/or launch the project

## 3. Tier 1 Milestones

### Milestone 1: Set Up the Project and Version Control

Create a basic C++ application, build it with CMake, create a local Git
repository and a GitHub repository, connect them, and push the first commit.

### Milestone 2: Create the Client and Server

Create separate C++ client and server programs that can each be built and run.

### Milestone 3: Establish the Initial TCP Connection

Complete the first prototype in which the client connects to the server over
TCP.

### Milestone 4: Establish Two-Way TCP Communication

Allow the client and server to send data to each other.

### Milestone 5: Set Up PostgreSQL Databases and Practise SQL

Create the databases needed by the client and server and practise basic SQL
and CRUD operations.

### Milestone 6: Access PostgreSQL from C++ Using pqxx

Use pqxx to let the client and server access their databases.

### Milestone 7: Integrate the Complete Data Flow

Connect the client database, client, TCP communication, server, and server
database into one working flow.

### Milestone 8: Handle Basic Errors

Handle the basic failure cases encountered during TCP communication and
database operations.

### Milestone 9: Complete Tier 1

Organize the build, launch, and development workflow and confirm that the
project can be built and run from the beginning.

## 4. After Tier 1

**TBD:** What will be built after Tier 1 has not been decided.

One possible future project is a receipt-processing application. A phone client
could send receipt photos, purchase screenshots, or other transaction inputs to
a home server. The server could organize the inputs and produce a CSV file for
MOZE. This is only a possible idea and is not currently defined as Tier 2.
