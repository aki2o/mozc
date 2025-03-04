// Copyright 2010-2021, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef MOZC_ENGINE_MINIMAL_ENGINE_H_
#define MOZC_ENGINE_MINIMAL_ENGINE_H_

#include <memory>
#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "converter/converter_interface.h"
#include "data_manager/data_manager_interface.h"
#include "dictionary/suppression_dictionary.h"
#include "engine/engine_interface.h"
#include "engine/user_data_manager_interface.h"
#include "prediction/predictor_interface.h"

namespace mozc {

// A minimal implementation of EngineInterface, which copies input key to the
// first candidate.
class MinimalEngine : public EngineInterface {
 public:
  MinimalEngine();
  MinimalEngine(const MinimalEngine &) = delete;
  MinimalEngine &operator=(const MinimalEngine &) = delete;

  ConverterInterface *GetConverter() const override;
  prediction::PredictorInterface *GetPredictor() const override;
  dictionary::SuppressionDictionary *GetSuppressionDictionary() override;
  bool Reload() override { return true; }
  bool ReloadAndWait() override { return true; }
  UserDataManagerInterface *GetUserDataManager() override;
  absl::string_view GetDataVersion() const override { return "0.0.0"; }
  const DataManagerInterface *GetDataManager() const override;
  std::vector<std::string> GetPosList() const override;

 private:
  std::unique_ptr<ConverterInterface> converter_;
  std::unique_ptr<prediction::PredictorInterface> predictor_;
  std::unique_ptr<dictionary::SuppressionDictionary> suppression_dictionary_;
  std::unique_ptr<UserDataManagerInterface> user_data_manager_;
  std::unique_ptr<const DataManagerInterface> data_manager_;
};

}  // namespace mozc

#endif  // MOZC_ENGINE_MINIMAL_ENGINE_H_
