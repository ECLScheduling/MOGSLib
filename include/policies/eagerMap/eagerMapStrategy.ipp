template<typename InputAdaptor>
void Strategy<InputAdaptor>::doTaskMapping(InputAdaptor &input) {
  /**
   * This is where the task mapping code is written.
   *
   *  Accessing the Strategy data:
   *    - The strategy data is where the input and output pointers can be accessed and modified. In order to access them, check: include/interfaces/strategy/strategyInterface.h
   *    - It is worth mentioning that the output is already allocated by default and must not be freed inside the library code. Altough, it's values must be changed by this method.
   *
   *  Getting the input information:
   *    - To check the functions to obtain the data from the input adaptor, see: include/interfaces/adaptor/defaultAdaptor.h
   *    - If you plan on using an adaptor extension to obtain more information as input, see the extension folder: include/interfaces/adaptor/extensions/
   *
   *  Writing re-usable code:
   *    - The subdirectory algorithms in the include folder is used to keep algorithm pieces that may be useful to other strategies. Write anything that might be reusable there.
   *    - The subdirectory adaptors in the include folder is where you can define custom adaptors to query specific data about the system. Bear in mind that \
   *      if you are building a new adaptor, there might be some tweaking to do in the different RTSs as this version of the library is still conceptually new.
   **/
}