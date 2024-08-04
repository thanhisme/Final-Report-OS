## Reader-Writer Problem

The Reader-Writer Problem is a fundamental synchronization issue in computer science, dealing with how to manage concurrent access to a shared resource. The objective is to coordinate access so that:

- **Multiple Readers**: Multiple readers can access the resource simultaneously as long as no writers are updating it.
- **Exclusive Writing**: Writers must have exclusive access to the resource, meaning no other readers or writers can interact with it while a write operation is ongoing.

### Key Goals

1. **Concurrent Reading**: Allow multiple readers to read the resource at the same time, provided there are no active writers.
2. **Exclusive Writing**: Ensure that when a writer is writing, no other readers or writers can access the resource.
3. **Fairness**: Prevent starvation by ensuring that neither readers nor writers are indefinitely blocked from accessing the resource.

### Reference:
[1] Wikipedia. (2015). Readers-Writers Problem. Retrieved on July 16, 2021, from [https://en.wikipedia.org/wiki/Readers%E2%80%93writers_problem](https://en.wikipedia.org/wiki/Readers%E2%80%93writers_problem)
