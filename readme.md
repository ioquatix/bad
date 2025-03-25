# Bad

Validate missing write barrier behaviour.

## Example Failure

```
verify_internal_consistency_reachable_i: WB miss (O->Y) (Bad::Object)Bad::Object -> (Hash)[A] 1
<internal:gc>:36: [BUG] gc_verify_internal_consistency: found internal inconsistency.
```
