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

An additional demo will run one client and one server on separate threads in a
single process. Session behavior and concurrent handling of multiple clients
remain **TBD**.

## 2. Confirmed Scope

### 2.1 System boundary

- The entire program runs on one Linux computer.
- The baseline contains one client program.
- The baseline contains one server program.
- The standalone client and server run as separate processes.
- An additional demo runs the same Client and Server classes on separate threads
  in a single process, still communicating over TCP.
- The client and server exchange data in both directions.

### 2.2 Technical learning constraints

- C++ is the implementation language
- Linux is the target operating system
- Client-server socket programming must be learned and demonstrated
- Multithreading is used in the integrated demo, including startup synchronization
  and coordinated shutdown
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

### Milestone 5: Set Up PostgreSQL Databases

Create the databases and tables needed by the client and server, load basic
data, and briefly practise CRUD operations to confirm that the database setup
works.

### Milestone 6: Integrate PostgreSQL into the Client and Server Using pqxx

Modify the existing client and server applications to use pqxx. The client reads
a question from the client database and sends it over TCP. The server looks up
the corresponding answer in the server database and sends the answer back.

### Milestone 7: Encapsulate the Client and Server into Classes

Create Client and Server classes, each with a header and implementation file.
Keep separate client_main.cpp and server_main.cpp entry points so both programs
can still run independently. Preserve the existing database-backed question and
answer behavior, and define socket ownership and cleanup responsibilities.

### Milestone 8: Handle Basic Errors

Handle empty query results, database exceptions, socket send/receive failures,
and peer disconnections. Handle partial sends and receives, report errors
clearly, and release resources on failure.

### Milestone 9: Build a Multithreaded Integration Demo

Add demo_main.cpp to run one Client and one Server on separate threads in a
single process while preserving the standalone executables. Synchronize startup
so the server is ready before the client connects. After the exchange, stop the
server and join all threads without hanging on a blocking accept().
Concurrent handling of multiple clients remains **TBD**.

### Milestone 10: Complete Tier 1

Document the build, database initialization, and launch workflow in the README.
Verify that the standalone client/server programs and the integrated demo can
be built and run by following those instructions.

## 4. After Tier 1

**TBD:** What will be built after Tier 1 has not been decided.

One possible future project is a receipt-processing application. A phone client
could send receipt photos, purchase screenshots, or other transaction inputs to
a home server. The server could organize the inputs and produce a CSV file for
MOZE. This is only a possible idea and is not currently defined as Tier 2.
