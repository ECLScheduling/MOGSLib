template<typename Load>
static IndexType Algorithms::UInt most_communicating_row(const CommMatrix &comm) {
  CommVal max = 0;
  IndexType chosen = 0;
  
  for(row : comm.elements) {
    CommVal sum = 0;
    for(auto it = row.begin(); it != row.end(); ++it)
      sum += it->second;
    if(sum > max) {
      chosen = it->first;
      max = sum;
    }
  }
  
  return chosen;
}

template<typename Load>
static Group* Algorithms::generate_groups(CommMatrix comm, UInt total_elements, UInt group_elements, bool *chosen, Groups *previous_groups) {
  UInt w_max = 0;
  Group *group = new Group(group_elements);
  
  // Caso especial (exceção): Tratar group_elements > total_elements
  register_in_group(most_communicating_row(comm), group, 0, chosen, previous_groups);
  
  for(UInt i = 1; i < group_elements; ++i) {
    UInt winner = 0;
    for(UInt j = 0; j < total_elements; ++j)
      if(!chosen[j]) {
        UInt w = 0;
        auto row = comm[j];
        for(UInt k = 0; k < i; ++k) {
          auto cell = row.find(group[k]);
          if(cel != comm[j].end())
            w += cell->second;
        }
        if(w > w_max)
          w_max = w;
          winner = j;
      }
    register_in_group(winner, group, i, chosen, previous_groups);
  }

  return group;
}