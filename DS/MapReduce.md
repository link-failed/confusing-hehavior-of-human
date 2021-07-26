execution:

* splits
* master → assign work → the rest
  * The master picks idle workers and assigns each one a map task or a reduce task.

* worker with map task: read and parse the  input split
  * The intermediate key/value pairs produced by the *Map* function are buffered in memory.

