
template<typename InputAdaptor>
void Strategy<InputAdaptor>::doTaskMapping() {
  debug_trc<LibStrategies>() << "Entering BinLPT Strategy Mapping...\n";

  /* Retrieve the input from the adaptor */
  InputAdaptor &input = *StrategyInterface<InputAdaptor>::currentInput;
  Load *task_loads = input.taskLoads();
  const UInt ntasks = input.ntasks();
  const UInt nchunks = input.structure();

  Load *PE_loads = input.PELoads();
  const UInt nPEs = input.nPEs();
  
  /* Partition the input into chunks */
  UInt *chunk_sizes = AlgorithmSet::compute_chunksizes(task_loads, ntasks, nchunks);
  Load *chunk_loads = AlgorithmSet::compute_chunkloads(task_loads, ntasks, chunk_sizes, nchunks);
  UInt *chunk_offset = UtilityAlgorithms::compute_cummulativesum<UInt, UInt>(chunk_sizes, nchunks);
  UInt *chunk_map = new UInt[nchunks];

  /* Initialize the chunk map for sorting */
  for(UInt i = 0; i < nchunks; ++i)
    chunk_map[i] = i;

  /* Sort the chunks by load */
  UtilityAlgorithms::insertion_sort<Load, UInt, true>(chunk_map, chunk_loads, nchunks); // Loads are sorted but the data not, use the chunk_map to get the correct chunk data about that load.

  /* Iterate over the chunks and assign to PEs */
  for (UInt i = nchunks; i > 0; --i) {
    const UInt idx = i-1;
    const UInt cur_chunk_idx = chunk_map[idx];
    UInt pe_id = 0;

    if(chunk_loads[idx] == 0)
      continue;

    /* Find the least overloaded PE to receive the task chunk. */
    for(UInt j = 0; j < nPEs; ++j) {
      if(PE_loads[j] < PE_loads[pe_id])
        pe_id = j;
    }

    /* Assign the tasks in the chunk to the PE. */
    for(UInt j = 0; j < chunk_sizes[cur_chunk_idx]; ++j) {
      StrategyInterface<InputAdaptor>::output[chunk_offset[cur_chunk_idx] + j] = pe_id;
    }

    /* Update the load on the pe */
    PE_loads[pe_id] += chunk_loads[idx];
  }

  for(UInt i = 0; i < nPEs; ++i)
    debug_trc<LibStrategies>() << "PE[" << i << "]: " << PE_loads[i] << "\n";

  /* Clean memory */
  delete [] chunk_sizes;
  delete [] chunk_loads;
  delete [] chunk_offset;
  delete [] chunk_map;

  debug_trc<LibStrategies>() << "Exiting BinLPT Strategy Mapping...\n";
}