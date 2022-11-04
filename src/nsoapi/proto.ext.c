void nsoapi$proto$$__ext_init__() {
    // NOP
}

nsoapi$proto$$IncompleteReadError nsoapi$proto$$IncompleteReadError$as_instance ($value x) {
    if ($ISINSTANCE(x, nsoapi$proto$$IncompleteReadError)->val) {
        return ((nsoapi$proto$$IncompleteReadError)x);
    }
    return $None;
}

$bool nsoapi$proto$$IncompleteReadError$is_instance ($value x) {
    return $ISINSTANCE(x, nsoapi$proto$$IncompleteReadError);
}

nsoapi$proto$$EObject nsoapi$proto$$EObject$as_instance ($value x) {
    if ($ISINSTANCE(x, nsoapi$proto$$EObject)->val) {
        return ((nsoapi$proto$$EObject)x);
    }
    return $None;
}

nsoapi$proto$$EList nsoapi$proto$$EList$as_instance ($value x) {
    if ($ISINSTANCE(x, nsoapi$proto$$EList)->val) {
        return ((nsoapi$proto$$EList)x);
    }
    return $None;
}
