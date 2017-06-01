# src

CS 551 Project 2: Publish and Subscribe IPCs (referencing JMS

Requirements:

The MINIX IPCs do not allow a user process (thread) to send a message to another. 

In this project, we ask you to design and implement a set of system calls 
that will allow user processes to send and receive messages to one another and with additional functionalities.

You are asked to implement at least the following system calls:

TopicLookup: that will allow a process to discover what interest groups are there.
TopicCreate: that will allow a process to create an interest group.
TopicPublisher: that will allow a process to declare itself a publisher of a specific interest group.
TopicSubscriber: that will allow a process to declare itself a subscriber to an interest group.
Publish: that will allow a publisher to send a message to an interest group.
Retrieve: that will allow a subscriber to retrieve one message from an interest group.

While a publisher is sending to a topic, no other user can publish to or retrieve from the topic. 

However, multiple subscribers can be retrieving messages from the same topic at the same time.
You will maintain a buffer that can contain 5 messages for each topic. 
No publisher can send to the topic when the buffer is full. 
On the other hand, Rretrieve is nonblocking. 
A message is removed from the buffer after it has been retrived by all the subscribers. 

A message is published once and retrieved by all subscribers who had subscribed to the topic 
before the message was published, at least once and at most once.

We ask you to specifically address these questions: 
Can deadlock occur with your IPCs? If not, why? If yes, do you detect deadlock and how? If so, how you can recover from it?. If you do not detect deadlock, you should also say why.  

-> No deadlock by using semaphore and sending error message if trying to publish if the buffer is full.

If deadlock can occur, can you advise the programmer to avoid it?

-> No deadlock
