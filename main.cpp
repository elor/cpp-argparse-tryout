#include <argparse/argparse.hpp>
#include <iostream>

int main(int argc, char **argv) {
  auto parser = argparse::ArgumentParser("main", "0.1");

  parser.add_argument("input")
      .help("input file")
      .default_value(std::string("input.txt"));

  parser.add_argument("-o", "--output")
      .help("output file")
      .default_value(std::string("output.txt"));

  parser.add_argument("-v", "--verbose")
      .help("increase output verbosity")
      .default_value(false)
      .implicit_value(true);

  parser.add_argument("-q", "--quiet")
      .help("decrease output verbosity")
      .default_value(false)
      .implicit_value(true);

  parser.add_argument("-n", "--number")
      .help("a number")
      .default_value(10)
      .action([](const std::string &value) { return std::stoi(value); });

  parser.add_argument("-C", "--counts")
      .help("multiple numbers, optional")
      .default_value(std::vector<int>())
      .nargs(argparse::nargs_pattern::any)
      .action([](const std::string &value) { return std::stoi(value); });

  try {
    parser.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cout << err.what() << std::endl;
    std::cout << "See --help for more information." << std::endl;
    exit(1);
  }

  std::cout << "input: " << parser.get<std::string>("input") << std::endl;
  std::cout << "output: " << parser.get<std::string>("output") << std::endl;
  std::cout << "verbose: " << parser.get<bool>("verbose") << std::endl;
  std::cout << "quiet: " << parser.get<bool>("quiet") << std::endl;
  std::cout << "number: " << parser.get<int>("number") << std::endl;
  std::cout << "counts: ";
  for (auto &count : parser.get<std::vector<int>>("counts")) {
    std::cout << count << " ";
  }
  std::cout << std::endl;

  return 0;
}
