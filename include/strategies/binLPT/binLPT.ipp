template<typename InputAdaptor>
void Strategy<InputAdaptor>::doTaskMapping() {
  
  /* Retrieve the input from the adaptor */
  InputAdaptor &input = *StrategyInterface<InputAdaptor>::currentInput;
  Load *task_loads = input.taskLoads().data();
  const UInt ntask = input.taskLoads().size();
  const UInt nchunks = input.structure();

  Load *pe_loads = input.PELoads().data();
  const UInt npes = input.PELoads().size();

  /* Partition the input into chunks */
  UInt *chunk_sizes = AlgorithmSet::compute_chunksizes(task_loads, ntasks, nchunks);
  Load *chunk_loads = AlgorithmSet::compute_chunkloads(task_loads, ntasks, chunk_sizes, nchunks);
  UInt *chunk_map = new UInt[nchunks];

  /* Initialize the chunk map for sorting */
  for(UInt i = 0; i < nchunks; ++i)
    chunk_map[i] = i;

  /* Sort the chunks by load */
  UtilityAlgorithms::insertion_sort<Load, UInt>(chunk_map, chunk_loads, nchunks);

  /* Iterate over the chunks and assign to PEs */
  for (UInt i = nchunks; i > 0; --i) {
    const UInt idx = i-1;
    UInt pe_id = 0;

    if(chunk_loads[idx] == 0)
      continue;

    /* Find the least overloaded PE to receive the task chunk. */
    for(UInt j = 0; j < npes; ++j) {
      if(pe_loads[j] < pe_loads[pe_id])
        pe_id = j;
    }

    //TODO: Assign the tasks in the chunk to the PE.
    for(UInt j = 0; j < chunk_sizes[chunk_map[idx]]; ++j) {
      output.set(pe_id, /* Task id */);
    }
    //pe_loads[] += task load
  }

  /* Clean memory */
  delete [] chunk_sizes;
  delete [] chunk_loads;
  delete [] chunk_map;
}