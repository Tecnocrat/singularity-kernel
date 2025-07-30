// Path: singularity-kernel/src/restore/threshold_manager.cpp
#include "threshold_manager.h"
#include <iostream>

using namespace Singularity;

ThresholdManager::ThresholdManager(double h, double c, RestoreCoherence& rc)
 : high_(h), critical_(c), rc_(rc) {}

void ThresholdManager::monitor(double entropyRate) {
  if (!checkpointed_ && entropyRate >= high_) {
    std::cout << "[THRESHOLD] High limit reached ("<<entropyRate<<") – checkpointing\n";
    checkpoint();
  }
  if (entropyRate >= critical_) {
    std::cout << "[THRESHOLD] Critical limit reached ("<<entropyRate<<") – rolling back\n";
    rollback();
  }
}

void ThresholdManager::checkpoint() {
  rc_.exportAICFrame("schema/checkpoint_frame");
  checkpointed_ = true;
}

void ThresholdManager::rollback() {
  // stub: reload last checkpoint, reinitialize seed
  std::cout << "[THRESHOLD] Rollback to last coherent frame\n";
  // TODO: implement actual state reload
}
