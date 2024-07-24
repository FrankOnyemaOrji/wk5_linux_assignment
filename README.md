To test if the project is working, you need to compile the server and client programs and then run them in different terminal windows. Here’s a step-by-step guide on how to do this:

### Step-by-Step Testing Guide

#### Compiling the Programs

1. **Open a Terminal Window**:
   - For Linux or macOS, open a terminal.
   - For Windows, open Command Prompt or PowerShell.

2. **Compile the Server Code**:
   - Navigate to the directory where your server code is located.
   - Compile the server code using `gcc`:
     ```sh
     gcc -o server server.c -pthread
     ```

3. **Compile the Client Code**:
   - Open another terminal window.
   - Navigate to the directory where your client code is located.
   - Compile the client code using `gcc`:
     ```sh
     gcc -o client client.c
     ```

#### Running the Server

1. **Run the Server Program**:
   - In the terminal window where you compiled the server, start the server:
     ```sh
     ./server
     ```

   - The server should start listening for incoming connections.

#### Running the Client

1. **Run the Client Program**:
   - In the terminal window where you compiled the client, start the client:
     ```sh
     ./client
     ```

2. **Testing the First Program (Logging System)**:
   - When prompted, enter a paragraph of text in the client terminal.
   - The client will send this message to the server.
   - The server should:
     - Save the message to a file named `received_message.txt` in the same directory as the server code.
     - Count the number of words in the message and send the word count back to the client.
   - The client should display the word count received from the server.

3. **Testing the Second Program (Chat System)**:
   - Start the server in one terminal window.
   - Start the client in another terminal window.
   - Type messages in the client terminal to send them to the server.
   - The server should display the message and prompt for a response.
   - Type a response in the server terminal to send it back to the client.
   - Continue this back-and-forth communication to test the chat functionality.

### Example of Testing

#### Testing the Logging System (Question 1)

1. **Run Server**:
   ```sh
   ./server
   ```
   The server will start and wait for incoming connections.

2. **Run Client**:
   ```sh
   ./client
   ```
   The client will prompt you to enter a paragraph of text:
   ```
   Enter a paragraph: This is a test paragraph to check the logging system.
   ```
   - The client sends this message to the server.
   - The server saves this message to `received_message.txt`.
   - The server counts the words and sends back:
   ```
   Word count: 8
   ```

#### Testing the Chat System (Question 2)

1. **Run Server**:
   ```sh
   ./server
   ```
   The server will start and wait for incoming connections.

2. **Run Client**:
   ```sh
   ./client
   ```
   The client will prompt you to enter a message:
   ```
   Client: Hello, Server!
   ```
   - The client sends this message to the server.
   - The server prints the message and prompts for a response:
   ```
   Client: Hello, Server!
   Server: Hi there, Client!
   ```
   - The server sends the response back to the client.
   - The client prints the server's response:
   ```
   Server: Hi there, Client!
   ```

### Verifying the Output

- **For the Logging System**:
  - Check that the `received_message.txt` file contains the message sent by the client.
  - Verify that the client receives the correct word count.

- **For the Chat System**:
  - Ensure that messages are correctly sent and received between the client and server.
  - Test multiple messages back and forth to verify continuous communication.

By following these steps, you can ensure that your socket programming project is working correctly.