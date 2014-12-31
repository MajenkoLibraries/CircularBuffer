CircularBuffer
==============

* Round-robin buffer template class.

This simple class emulates a Stream object and works in a similar way.  Note that
due to the flexible template nature of the library it cannot directly inherit the
Stream class, so it cannot be used in polymorphic situations.

That said, the class does have the familiar .read(), .write() and .available()
functions you're used to with the Stream class.

To use the class you first must define a buffer, its size, and most importantly, its
content type:

    CircularBuffer<int> myBuffer(64);

That, for example, will create a circular buffer consisting of 64 integers.  You can
even do it with floating point values:

    CircularBuffer<float> myBuffer(64);

Adding data to the buffer is as simple as:

    myBuffer.write(myValue);

You can see if there is any data available in the buffer with:

    if (myBuffer.available()) { ... }

And retrieve an item of data from it with:

    myValue = myBuffer.read();

In all instances *myValue* should be the same type as the content type of the buffer.

There are also a couple of extra utility functions:

* Purge all the data from the buffer:

    `myBuffer.clear();`

* Retrieve a specific entry *n* from the buffer:

    `myValue = myBuffer.getEntry(n);`

* Get the current *head* pointer value:

    `uint32_t head = myByffer.getHead();`

* Get the current *tail* pointer value:

    `uint32_t tail = myBuffer.getTail();`

The last two don't return content, they just return the position within the
buffer that the head and tail point to.  You can then use those in conjunction
with myBuffer.getEntry(n) to *peek* at the content of the buffer.
