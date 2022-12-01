void nsoapi$proto$$__ext_init__() {
    // NOP
}

$str nsoapi$proto$$ETuple$__str__ (nsoapi$proto$$ETuple self) {
    $Iterable w$3531 = (($Iterable)$Sequence$list$new()->w$Collection);
    $Collection w$3614 = $Sequence$list$new()->w$Collection;
    $Sequence w$3503 = (($Sequence)$Sequence$list$new());
    $Plus w$3551 = (($Plus)$Times$str$new());
    $Iterable w$3607 = (($Iterable)$Sequence$list$new()->w$Collection);
    $list sl = (($list (*) ($Collection, $Iterable, $list))w$3503->w$Collection->$class->__fromiter__)(w$3503->w$Collection, (($Iterable)$Collection$list$witness), $list$new(NULL, NULL));
    $Iterator n$6iter = (($Iterator (*) ($Iterable, $list))w$3531->$class->__iter__)(w$3531, self->elems);
    nsoapi$proto$$EObject n$7val = ((nsoapi$proto$$EObject (*) ($Iterator))n$6iter->$class->__next__)(n$6iter);
    while ($ISNOTNONE(n$7val)->val) {
        nsoapi$proto$$EObject e = n$7val;
        (($NoneType (*) ($Sequence, $list, $str))w$3503->$class->append)(w$3503, sl, (($str)$str$new((($value)e))));
        n$7val = ((nsoapi$proto$$EObject (*) ($Iterator))n$6iter->$class->__next__)(n$6iter);
    }
    return (($str (*) ($Plus, $str, $str))w$3551->$class->__add__)(w$3551, (($str (*) ($Plus, $str, $str))w$3551->$class->__add__)(w$3551, to$str("("), ({ $str $tmp = to$str(", ");
                                                                                                                                                           (($str (*) ($str, $Iterable, $list))$tmp->$class->join)($tmp, w$3607, sl); })), to$str(")"));
}

$str nsoapi$proto$$EList$__str__ (nsoapi$proto$$EList self) {
    $Iterable w$3531 = (($Iterable)$Sequence$list$new()->w$Collection);
    $Collection w$3615 = $Sequence$list$new()->w$Collection;
    $Sequence w$3503 = (($Sequence)$Sequence$list$new());
    $Plus w$3551 = (($Plus)$Times$str$new());
    $Iterable w$3607 = (($Iterable)$Sequence$list$new()->w$Collection);
    $list sl = (($list (*) ($Collection, $Iterable, $list))w$3503->w$Collection->$class->__fromiter__)(w$3503->w$Collection, (($Iterable)$Collection$list$witness), $list$new(NULL, NULL));
    $Iterator n$6iter = (($Iterator (*) ($Iterable, $list))w$3531->$class->__iter__)(w$3531, self->elems);
    nsoapi$proto$$EObject n$7val = ((nsoapi$proto$$EObject (*) ($Iterator))n$6iter->$class->__next__)(n$6iter);
    while ($ISNOTNONE(n$7val)->val) {
        nsoapi$proto$$EObject e = n$7val;
        (($NoneType (*) ($Sequence, $list, $str))w$3503->$class->append)(w$3503, sl, (($str)$str$new((($value)e))));
        n$7val = ((nsoapi$proto$$EObject (*) ($Iterator))n$6iter->$class->__next__)(n$6iter);
    }
    return (($str (*) ($Plus, $str, $str))w$3551->$class->__add__)(w$3551, (($str (*) ($Plus, $str, $str))w$3551->$class->__add__)(w$3551, to$str("["), ({ $str $tmp = to$str(", ");
                                                                                                                                                           (($str (*) ($str, $Iterable, $list))$tmp->$class->join)($tmp, w$3607, sl); })), to$str("]"));
}
