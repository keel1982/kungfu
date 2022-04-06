#include "py-longfist.h"

#include <kungfu/longfist/longfist.h>

using namespace kungfu::longfist::enums;

namespace py = pybind11;

namespace kungfu::longfist::pybind {

void bind_enums(py::module &m) {
  auto m_enums = m.def_submodule("enums");

  py::enum_<mode>(m_enums, "mode", py::arithmetic(), "Kungfu Run Mode")
      .value("LIVE", mode::LIVE)
      .value("DATA", mode::DATA)
      .value("REPLAY", mode::REPLAY)
      .value("BACKTEST", mode::BACKTEST)
      .export_values();
  m_enums.def("get_mode_name", &get_mode_name);
  m_enums.def("get_mode_by_name", &get_mode_by_name);

  py::enum_<category>(m_enums, "category", py::arithmetic(), "Kungfu Data Category")
      .value("MD", category::MD)
      .value("TD", category::TD)
      .value("STRATEGY", category::STRATEGY)
      .value("SYSTEM", category::SYSTEM)
      .export_values();
  m_enums.def("get_category_name", &get_category_name);
  m_enums.def("get_category_by_name", &get_category_by_name);

  py::enum_<layout>(m_enums, "layout", py::arithmetic(), "Kungfu Data Layout")
      .value("JOURNAL", layout::JOURNAL)
      .value("SQLITE", layout::SQLITE)
      .value("NANOMSG", layout::NANOMSG)
      .value("LOG", layout::LOG)
      .export_values();
  m_enums.def("get_layout_name", &get_layout_name);

  py::enum_<InstrumentType>(m_enums, "InstrumentType", py::arithmetic())
      .value("Unknown", InstrumentType::Unknown)
      .value("Stock", InstrumentType::Stock)
      .value("Future", InstrumentType::Future)
      .value("Bond", InstrumentType::Bond)
      .value("StockOption", InstrumentType::StockOption)
      .value("Fund", InstrumentType::Fund)
      .value("TechStock", InstrumentType::TechStock)
      .value("Index", InstrumentType::Index)
      .value("Repo", InstrumentType::Repo)
      .value("Crypto", InstrumentType::Crypto)
      .export_values()
      .def("__eq__", [](const InstrumentType &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<CommissionRateMode>(m_enums, "CommissionRateMode", py::arithmetic())
      .value("ByAmount", CommissionRateMode::ByAmount)
      .value("ByVolume", CommissionRateMode::ByVolume)
      .export_values()
      .def("__eq__", [](const CommissionRateMode &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<ExecType>(m_enums, "ExecType", py::arithmetic())
      .value("Unknown", ExecType::Unknown)
      .value("Cancel", ExecType::Cancel)
      .value("Trade", ExecType::Trade)
      .export_values()
      .def("__eq__", [](const ExecType &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<Side>(m_enums, "Side", py::arithmetic())
      .value("Buy", Side::Buy)
      .value("Sell", Side::Sell)
      .value("Lock", Side::Lock)
      .value("Unlock", Side::Unlock)
      .value("Exec", Side::Exec)
      .value("Drop", Side::Drop)
      .value("Purchase", Side::Purchase)
      .value("Redemption", Side::Redemption)
      .value("Split", Side::Split)
      .value("Merge", Side::Merge)
      .value("MarginTrade", Side::MarginTrade)
      .value("ShortSell", Side::ShortSell)
      .value("RepayMargin", Side::RepayMargin)
      .value("RepayStock", Side::RepayStock)
      .value("CashRepayMargin", Side::CashRepayMargin)
      .value("StockRepayStock", Side::StockRepayStock)
      .value("SurplusStockTransfer", Side::SurplusStockTransfer)
      .value("GuaranteeStockTransferIn", Side::GuaranteeStockTransferIn)
      .value("GuaranteeStockTransferOut", Side::GuaranteeStockTransferOut)
      .value("Unknown", Side::Unknown)
      .export_values()
      .def("__eq__", [](const Side &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<Offset>(m_enums, "Offset", py::arithmetic())
      .value("Open", Offset::Open)
      .value("Close", Offset::Close)
      .value("CloseToday", Offset::CloseToday)
      .value("CloseYesterday", Offset::CloseYesterday)
      .export_values()
      .def("__eq__", [](const Offset &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<HedgeFlag>(m_enums, "HedgeFlag", py::arithmetic())
      .value("Speculation", HedgeFlag::Speculation)
      .value("Arbitrage", HedgeFlag::Arbitrage)
      .value("Hedge", HedgeFlag::Hedge)
      .value("Covered", HedgeFlag::Covered)
      .export_values()
      .def("__eq__", [](const HedgeFlag &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<BsFlag>(m_enums, "BsFlag", py::arithmetic())
      .value("Unknown", BsFlag::Unknown)
      .value("Buy", BsFlag::Buy)
      .value("Sell", BsFlag::Sell)
      .export_values()
      .def("__eq__", [](const BsFlag &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<OrderStatus>(m_enums, "OrderStatus", py::arithmetic())
      .value("Unknown", OrderStatus::Unknown)
      .value("Submitted", OrderStatus::Submitted)
      .value("Pending", OrderStatus::Pending)
      .value("Cancelled", OrderStatus::Cancelled)
      .value("Error", OrderStatus::Error)
      .value("Filled", OrderStatus::Filled)
      .value("PartialFilledNotActive", OrderStatus::PartialFilledNotActive)
      .value("PartialFilledActive", OrderStatus::PartialFilledActive)
      .export_values()
      .def("__eq__", [](const OrderStatus &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<Direction>(m_enums, "Direction", py::arithmetic())
      .value("Long", Direction::Long)
      .value("Short", Direction::Short)
      .export_values()
      .def("__eq__", [](const Direction &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<PriceType>(m_enums, "PriceType", py::arithmetic())
      .value("Any", PriceType::Any)
      .value("FakBest5", PriceType::FakBest5)
      .value("Fak", PriceType::Fak)
      .value("Fok", PriceType::Fok)
      .value("Limit", PriceType::Limit)
      .value("ForwardBest", PriceType::ForwardBest)
      .value("ReverseBest", PriceType::ReverseBest)
      .export_values()
      .def("__eq__", [](const PriceType &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<VolumeCondition>(m_enums, "VolumeCondition", py::arithmetic())
      .value("Any", VolumeCondition::Any)
      .value("Min", VolumeCondition::Min)
      .value("All", VolumeCondition::All)
      .export_values()
      .def("__eq__", [](const VolumeCondition &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<TimeCondition>(m_enums, "TimeCondition", py::arithmetic())
      .value("IOC", TimeCondition::IOC)
      .value("GFD", TimeCondition::GFD)
      .value("GTC", TimeCondition::GTC)
      .export_values()
      .def("__eq__", [](const TimeCondition &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<OrderActionFlag>(m_enums, "OrderActionFlag", py::arithmetic())
      .value("Cancel", OrderActionFlag::Cancel)
      .export_values()
      .def("__eq__", [](const OrderActionFlag &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<LedgerCategory>(m_enums, "LedgerCategory", py::arithmetic())
      .value("Account", LedgerCategory::Account)
      .value("Strategy", LedgerCategory::Strategy)
      .export_values()
      .def("__eq__", [](const LedgerCategory &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<BrokerState>(m_enums, "BrokerState", py::arithmetic())
      .value("Pending", BrokerState::Pending)
      .value("Idle", BrokerState::Idle)
      .value("DisConnected", BrokerState::DisConnected)
      .value("Connected", BrokerState::Connected)
      .value("LoggedIn", BrokerState::LoggedIn)
      .value("LoginFailed", BrokerState::LoginFailed)
      .value("Ready", BrokerState::Ready)
      .export_values()
      .def("__eq__", [](const BrokerState &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<StrategyState>(m_enums, "StrategyState", py::arithmetic())
      .value("Normal", StrategyState::Normal)
      .value("Warn", StrategyState::Warn)
      .value("Error", StrategyState::Error)
      .export_values()
      .def("__eq__", [](const StrategyState &a, int b) { return static_cast<int>(a) == b; });

  py::enum_<MarketType>(m_enums, "MarketType", py::arithmetic())
      .value("kNone", MarketType::kNone)
      .value("kNEEQ", MarketType::kNEEQ)
      .value("kSHFE", MarketType::kSHFE)
      .value("kCFFEX", MarketType::kCFFEX)
      .value("kDCE", MarketType::kDCE)
      .value("kCZCE", MarketType::kCZCE)
      .value("kINE", MarketType::kINE)
      .value("kSSE", MarketType::kSSE)
      .value("kSZSE", MarketType::kSZSE)
      .value("kHKEx", MarketType::kHKEx)
      .value("kMax", MarketType::kMax)
      .export_values()
      .def("__eq__", [](const MarketType &a, int b) { return static_cast<int>(a) == b; });
  
  py::enum_<SubscribeSecuDataType>(m_enums, "SubscribeSecuDataType", py::arithmetic())
      .value("kNone", SubscribeSecuDataType::kNone)
      .value("kSnapshot", SubscribeSecuDataType::kSnapshot)
      .value("kTickExecution", SubscribeSecuDataType::kTickExecution)
      .value("kTickOrder", SubscribeSecuDataType::kTickOrder)
      .value("kOrderQueue", SubscribeSecuDataType::kOrderQueue)
      .export_values()
      .def("__eq__", [](const SubscribeSecuDataType &a, uint64_t b) { return static_cast<uint64_t>(a) == b; })
      .def("__or__", py::overload_cast<const SubscribeSecuDataType &, const SubscribeSecuDataType &>(&sub_data_bitwise<SubscribeSecuDataType, uint64_t>));
  
  py::enum_<SubscribeCategoryType>(m_enums, "SubscribeCategoryType", py::arithmetic())
      .value("kNone", SubscribeCategoryType::kNone)
      .value("kStock", SubscribeCategoryType::kStock)
      .value("kFund", SubscribeCategoryType::kFund)
      .value("kBond", SubscribeCategoryType::kBond)
      .value("kIndex", SubscribeCategoryType::kIndex)
      .value("kHKT", SubscribeCategoryType::kHKT)
      .value("kOption", SubscribeCategoryType::kOption)
      .value("kFutureOption", SubscribeCategoryType::kFutureOption)
      .value("kOthers", SubscribeCategoryType::kOthers)
      .export_values()
      .def("__eq__", [](const SubscribeCategoryType &a, int b) { return static_cast<int>(a) == b; })
      .def("__or__", py::overload_cast<const SubscribeCategoryType &, const SubscribeCategoryType &>(&sub_data_bitwise<SubscribeCategoryType, uint64_t>));
}
} // namespace kungfu::longfist::pybind
