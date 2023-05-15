void acton_streamerQ_nsoapiQ_protoQ___ext_init__() {
    // NOP
}

B_str acton_streamerQ_nsoapiQ_protoQ_EListD___str__ (acton_streamerQ_nsoapiQ_protoQ_EList self) {
    B_Iterable W_4021 = ((B_Iterable)B_SequenceD_listG_new()->W_Collection);
    B_Collection W_4104 = B_SequenceD_listG_new()->W_Collection;
    B_Sequence W_3993 = ((B_Sequence)B_SequenceD_listG_new());
    B_Plus W_4041 = ((B_Plus)B_TimesD_strG_new());
    B_Iterable W_4097 = ((B_Iterable)B_SequenceD_listG_new()->W_Collection);
    B_list sl = ((B_list (*) (B_Collection, B_Iterable, B_list))W_3993->W_Collection->$class->__fromiter__)(W_3993->W_Collection, ((B_Iterable)$CollectionD_listG_witness), B_listG_new(NULL, NULL));
    B_Iterator N_6iter = ((B_Iterator (*) (B_Iterable, B_list))W_4021->$class->__iter__)(W_4021, self->elems);
    acton_streamerQ_nsoapiQ_protoQ_EObject N_7val = ((acton_streamerQ_nsoapiQ_protoQ_EObject (*) (B_Iterator))N_6iter->$class->__next__)(N_6iter);
    while ($ISNOTNONE(N_7val)->val) {
        acton_streamerQ_nsoapiQ_protoQ_EObject e = N_7val;
        ((B_NoneType (*) (B_Sequence, B_list, B_str))W_3993->$class->append)(W_3993, sl, ((B_str)B_strG_new(((B_value)e))));
        N_7val = ((acton_streamerQ_nsoapiQ_protoQ_EObject (*) (B_Iterator))N_6iter->$class->__next__)(N_6iter);
    }
    return ((B_str (*) (B_Plus, B_str, B_str))W_4041->$class->__add__)(W_4041, ((B_str (*) (B_Plus, B_str, B_str))W_4041->$class->__add__)(W_4041, to$str("["), ({ B_str $tmp = to$str(", ");
                                                                                                                                                                   ((B_str (*) (B_str, B_Iterable, B_list))$tmp->$class->join)($tmp, W_4097, sl); })), to$str("]"));
}

B_str acton_streamerQ_nsoapiQ_protoQ_ETupleD___str__ (acton_streamerQ_nsoapiQ_protoQ_ETuple self) {
    B_Collection W_4619 = B_SequenceD_listG_new()->W_Collection;
    B_Iterable W_4669 = ((B_Iterable)B_SequenceD_listG_new()->W_Collection);
    B_Sequence W_4508 = ((B_Sequence)B_SequenceD_listG_new());
    B_Plus W_4556 = ((B_Plus)B_TimesD_strG_new());
    B_Iterable W_4612 = ((B_Iterable)B_SequenceD_listG_new()->W_Collection);
    B_list sl = ((B_list (*) (B_Collection, B_Iterable, B_list))W_4508->W_Collection->$class->__fromiter__)(W_4508->W_Collection, ((B_Iterable)$CollectionD_listG_witness), B_listG_new(NULL, NULL));
    B_Iterator N_12iter = ((B_Iterator (*) (B_Iterable, B_list))W_4669->$class->__iter__)(W_4669, self->elems);
    acton_streamerQ_nsoapiQ_protoQ_EObject N_13val = ((acton_streamerQ_nsoapiQ_protoQ_EObject (*) (B_Iterator))N_12iter->$class->__next__)(N_12iter);
    while ($ISNOTNONE(N_13val)->val) {
        acton_streamerQ_nsoapiQ_protoQ_EObject e = N_13val;
        ((B_NoneType (*) (B_Sequence, B_list, B_str))W_4508->$class->append)(W_4508, sl, ((B_str)B_strG_new(((B_value)e))));
        N_13val = ((acton_streamerQ_nsoapiQ_protoQ_EObject (*) (B_Iterator))N_12iter->$class->__next__)(N_12iter);
    }
    return ((B_str (*) (B_Plus, B_str, B_str))W_4556->$class->__add__)(W_4556, ((B_str (*) (B_Plus, B_str, B_str))W_4556->$class->__add__)(W_4556, to$str("("), ({ B_str $tmp = to$str(", ");
                                                                                                                                                                   ((B_str (*) (B_str, B_Iterable, B_list))$tmp->$class->join)($tmp, W_4612, sl); })), to$str(")"));
}
