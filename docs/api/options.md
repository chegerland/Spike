# Options
```cpp
class Options
{
private:

  std::string file; // path to parameter file

public:

  // constructor
  Options(std::string file);
  Options(int argc, char * argv[]);

  // check input options
  void check();

  // getter function
  std::string get_file();

};
```
