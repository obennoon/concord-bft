// Concord
//
// Copyright (c) 2018 VMware, Inc. All Rights Reserved.
//
// This product is licensed to you under the Apache 2.0 license (the "License").  You may not use this product except in
// compliance with the Apache 2.0 License.
//
// This product may include a number of subcomponents with separate copyright notices and license terms. Your use of
// these subcomponents is subject to the terms and conditions of the subcomponent's license, as noted in the LICENSE
// file.

#include "ReqMissingDataMsg.hpp"
#include "assertUtils.hpp"
#include "Crypto.hpp"

namespace bftEngine {
namespace impl {

ReqMissingDataMsg::ReqMissingDataMsg(ReplicaId senderId, ViewNum v, SeqNum s)
    : MessageBase(senderId, MsgCode::ReqMissingData, sizeof(ReqMissingDataMsgHeader)) {
  b()->viewNum = v;
  b()->seqNum = s;
  resetFlags();
}

void ReqMissingDataMsg::resetFlags() { b()->flags = 0; }

void ReqMissingDataMsg::validate(const ReplicasInfo& repInfo) {
  if (size() < sizeof(ReqMissingDataMsgHeader) ||
      senderId() ==
          repInfo.myId() ||  // TODO(GG) - TBD: we should use Assert for this condition (also in other messages)
      !repInfo.isIdOfReplica(senderId()))
    throw std::runtime_error(__PRETTY_FUNCTION__);
}

}  // namespace impl
}  // namespace bftEngine
