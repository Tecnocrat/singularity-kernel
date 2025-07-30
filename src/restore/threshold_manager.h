// Path: singularity-kernel/src/restore/threshold_manager.h
#pragma once
#include "restore_coherence.h"

namespace Singularity {
  class ThresholdManager {
  public:
    ThresholdManager(double high, double critical, RestoreCoherence& rc);
    void monitor(double entropyRate);

  private:
    double high_, critical_;
    RestoreCoherence& rc_;
    bool checkpointed_ = false;
    void checkpoint();
    void rollback();
  };
}
