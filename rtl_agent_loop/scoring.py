from __future__ import annotations

from typing import Any


def _metric_value(metrics: dict[str, Any], name: str) -> float | None:
    if name in metrics:
        value = metrics[name]
        if isinstance(value, (int, float)):
            return float(value)
    return None


def flatten_metrics(vivado_metrics: dict[str, Any] | None, perf_metrics: dict[str, Any] | None) -> dict[str, float]:
    flattened: dict[str, float] = {}
    if vivado_metrics:
        util = vivado_metrics.get("utilization", {})
        timing = vivado_metrics.get("timing", {})
        mapping = {
            "lut": util.get("lut"),
            "ff": util.get("ff"),
            "dsp": util.get("dsp"),
            "bram": util.get("bram"),
            "wns_ns": timing.get("wns_ns"),
            "fmax_mhz_est": timing.get("fmax_mhz_est"),
        }
        for key, value in mapping.items():
            if isinstance(value, (int, float)):
                flattened[key] = float(value)
    if perf_metrics:
        for key in ("latency_cycles", "latency_time_ms", "throughput_inferences_per_sec"):
            value = perf_metrics.get(key)
            if isinstance(value, (int, float)):
                flattened[key] = float(value)
    return flattened


def score_candidate(
    weights_cfg: dict[str, Any],
    vivado_metrics: dict[str, Any] | None,
    perf_metrics: dict[str, Any] | None,
    stage_failed: bool,
) -> dict[str, Any]:
    weights = weights_cfg["weights"]
    penalties = weights_cfg["penalties"]
    metrics = flatten_metrics(vivado_metrics, perf_metrics)

    total = 0.0
    breakdown: dict[str, float] = {}
    missing_metrics: list[str] = []

    for metric_name, weight in weights.items():
        value = _metric_value(metrics, metric_name)
        if value is None:
            total += penalties["missing_metric"]
            breakdown[f"missing:{metric_name}"] = penalties["missing_metric"]
            missing_metrics.append(metric_name)
            continue
        contribution = value * float(weight)
        total += contribution
        breakdown[metric_name] = contribution

    wns_value = _metric_value(metrics, "wns_ns")
    if wns_value is None:
        total += penalties["timing_missing"]
        breakdown["penalty:timing_missing"] = penalties["timing_missing"]
    elif wns_value < 0:
        total += penalties["timing_negative_wns"]
        breakdown["penalty:timing_negative_wns"] = penalties["timing_negative_wns"]

    if stage_failed:
        total += penalties["stage_failed"]
        breakdown["penalty:stage_failed"] = penalties["stage_failed"]

    return {
        "total_score": total,
        "breakdown": breakdown,
        "metrics": metrics,
        "missing_metrics": missing_metrics,
    }

