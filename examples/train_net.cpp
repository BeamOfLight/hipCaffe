// Copyright 2013 Yangqing Jia
//
// This is a simple script that allows one to quickly train a network whose
// parameters are specified by text format protocol buffers.
// Usage:
//    train_net net_proto_file solver_proto_file

#include <cuda_runtime.h>

#include <cstring>

#include "caffe/caffe.hpp"

using namespace caffe;

int main(int argc, char** argv) {
  cudaSetDevice(0);
  Caffe::set_mode(Caffe::GPU);
  Caffe::set_phase(Caffe::TRAIN);

  NetParameter net_param;
  ReadProtoFromTextFile(argv[1], &net_param);
  vector<Blob<float>*> bottom_vec;
  Net<float> caffe_net(net_param, bottom_vec);

  SolverParameter solver_param;
  ReadProtoFromTextFile(argv[2], &solver_param);

  LOG(ERROR) << "Starting Optimization";
  SGDSolver<float> solver(solver_param);
  solver.Solve(&caffe_net);
  LOG(ERROR) << "Optimization Done.";

  return 0;
}