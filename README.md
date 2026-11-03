# Remote File Command Server

A client-server application written in C that allows clients to manage files through a TCP connection.

The system provides a command-based interface for creating, reading, writing, appending, and deleting files stored on the server.

## Features

- TCP-based client-server communication.
- File creation, reading, writing, appending, and deletion.
- Input validation and command verification.
- Error handling with descriptive server responses.
- Support for executing multiple commands during a single client connection.
- Filename validation and protection against oversized commands.
- Modular architecture with separate components for networking, command processing, and file operations.

## Technologies

| Component | Technology |
|---|---|
| Programming Language | C |
| Operating System | Windows |
| Networking Library | Winsock2 |
| Network Protocol | TCP / IPv4 |
| Compiler | GCC (MinGW) |

## Architecture

The application consists of two main components:

**Server**

The server listens for incoming TCP connections, receives commands, validates the input, processes the requested operations, and sends responses back to the client.

**Client**

The client establishes a TCP connection with the server, accepts commands from the user, sends them to the server, and displays the received responses.

The communication is configured to use:

- **IP Address:** `127.0.0.1`
- **Port:** `8080`
- **Protocol:** TCP

## Supported Commands

| Command | Description |
|---|---|
| `CREATE <filename>` | Creates a new file on the server. |
| `READ <filename>` | Reads the contents of an existing file. |
| `WRITE <filename> <content>` | Replaces the contents of an existing file. |
| `APPEND <filename> <content>` | Appends content to an existing file. |
| `DELETE <filename>` | Deletes an existing file. |
| `EXIT` | Disconnects the client from the server. |

### Example Usage

```text
CREATE notes.txt
WRITE notes.txt Hello World
READ notes.txt
APPEND notes.txt Goodbye
DELETE notes.txt
EXIT
```

Each command is entered separately through the client terminal.

## Installation and Usage

### Requirements

- Windows operating system.
- GCC compiler (MinGW).
- PowerShell or another compatible terminal.

### Step 1: Clone the Repository

```bash
git clone https://github.com/yonatan9012/Remote-File-Command-Server.git
cd Remote-File-Command-Server
```

### Step 2: Configure the Server Directory

Open `server/server_init.c` and update the file storage directory path to match your local environment.

Make sure the parent directory exists and the application has the necessary permissions.

### Step 3: Compile the Server

```bash
gcc -Wall -Wextra server/*.c -o server.exe -lws2_32
```

### Step 4: Compile the Client

```bash
gcc -Wall -Wextra client/*.c -o client.exe -lws2_32
```

### Step 5: Run the Application

Open two terminal windows.

**Terminal 1 — Start the server:**

```powershell
.\server.exe
```

**Terminal 2 — Start the client:**

```powershell
.\client.exe
```

Once connected, enter any supported command in the client terminal to interact with the server.