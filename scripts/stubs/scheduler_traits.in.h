template<>
struct SchedulerTraits<SchedulerEnum::$TNAME$> {
  static std::string name() { return "$TNAME$"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::$DEPS$<Concepts...>;
};