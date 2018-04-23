template<typename Load>
typename Algorithms<Load>::IndexType Algorithms<Load>::most_communicating_row(const CommMatrix &comm) {
  CommVal max = 0;
  IndexType chosen = 0;
  
  for(UInt i = 0; i < comm.elements.size(); ++i) {
    auto row = comm.elements[i];
    CommVal sum = 0;
    for(auto it = row.begin(); it != row.end(); ++it)
      sum += it->second;
    if(sum > max) {
      chosen = i;
      max = sum;
    }
  }
  
  return chosen;
}

template<typename Load>
typename Algorithms<Load>::Group* Algorithms<Load>::generate_groups(CommMatrix &comm, UInt total_elements, UInt group_elements, bool *chosen, Group *previous_groups) {
  UInt w_max = 0;
  Group *group = new Group(group_elements);
  
  group->register_element(most_communicating_row(comm), 0, chosen, previous_groups);
  
  for(UInt i = 1; i < group_elements; ++i) {
    UInt winner = 0;
    for(UInt j = 0; j < total_elements; ++j)
      if(!chosen[j]) {
        UInt w = 0;
        auto row = comm[j];
        for(UInt k = 0; k < i; ++k) {
          auto cell = row.find(group->members[k]);
          if(cell != row.end()){
            w += cell->second;
          }
        }
        if(w > w_max) {
          w_max = w;
          winner = j;
        }
      }
    group->register_element(winner, i, chosen, previous_groups);
  }
  return group;
}

template<typename Load>
void Algorithms<Load>::recreate_matrix(CommMatrix &comm, Group *groups, const UInt &ngroups) {

}