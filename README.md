# Client Program - SOA Final Project: Real-Time Scheduler Simulator, Cheddar++
Made by:
- Ángel Javier Díaz Balboa (alu0101432632@ull.edu.es)
- Cristopher Manuel Afonso Mora (alu0101402031@ull.edu.es)
- Cheuk Kelly Ng Pante (alu0101364544@ull.edu.es)

# Description
In this project we have programmaed a real-time scheduler simulator inspired by Cheddar. We have used QT Creator framework (version 6.5.1) to make this project. This program acts as a client and connects (via TCP) to the server to introduce data to the database. The main function of this program is to simulate a real-time scheduler with the Rate Monothonic algorithm. As well as, it can send/receive images to/from the server.

# Usage
When we first open **Cheddar++ Client** we will see three tabs:
- `Messages`: In this tab we can see the messages that the server sends to the client.
- `Simulation`: In this tab we can see the simulation of the tasks that we have introduced.
- `Image from server`: In this tab we can see the images that the server sends to the client.

In addition, we can see different icons on the left side of the window that allow us to do different actions:
- `Send image`: This icon allows us to send an image to the server.
- `Receive image`: This icon allows us to receive an image from the server.
- `Connection`: This icon allows us to connect/disconnect to/from the server.
- `Run simulation`: This icon allows us to run the simulation of the tasks that we have introduced.
- `Clear graph`: This icon allows us to clear the simulation graph.
- `Exit`: This icon allows us to exit the program.

### File transferences 
It displayed and we can see three options: `Send image`, `Receive image` and `Connection`. It works as equal as the icons that we have explained before.

(image_File_transferences)

### Simulation
It displayed and we can see two options: `Tasks` and `Run simulation`. The `Tasks` option it display a windows that allows us to introduce the tasks that we want to simulate. In this window we can see the following options:

(image_SimulationTasks)

We can introduce the tasks that we want to simulate with a "Name task", "Time of Task", "Period" and "Deadline". In addition, we can see two buttons: `Add task` and `Clean list`. The `Add task` button allows us to add a new task to a table to see all the tasks that we have introduced. The `Clean list` button allows us to clean the task that we have introduced. Besides, we can see a `Delete Task` button that allows us to delete a task from the table by clicking on the task/row that we want to delete.

The `Run simulation` option, on the *Simulation tab*, allows to run the simulation of the tasks that we have introduced. The same as the `Run simulation` icon that we have explained before.

## TCP Client
The TCP client is the main class of the program. It is in charge of connecting to the server, sending and receiving messages from the server. It is also in charge of sending and receiving images from the server. It is also in charge of running the simulation of the tasks that we have introduced. To connect to the server we have the icon and if we press it, it will display a window that allows us to introduce the IP and the port of the server that we want to connect to. If we press the `Connect` button, it will connect to the server. If we press the `Disconnect` button, it will disconnect from the server.

(image_Connect)
