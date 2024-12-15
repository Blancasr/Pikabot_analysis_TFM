/*
i = EBP + -0x18
ptr_2_data = EBP + -0x68
ptr_2_data_2 = EBP + -0x6c
j = EBP + -0x50
half_size_ofRawData = EBP + -0xb4
ptr_ImportTable2 = EBP +  -0x20
name = EBP + -0xbc
FirstThunk = EBP + -0x14
TLSTable = EBP + -0x200
AddressOfCallBacks = EBP + -0x30
Callback = EBP + -0xcc
AddressOfEntryPoint = EBP + -0xd0
*/

undefined repair_execute_stage2(){
    int ret_val = 0

    if (section_table_hasIMport == 0){
        ret_val = 0;
    } else {
        int i = 0;
        while (i < var7c){
            RawDataByte = ptr_stage2 + ptrRawData + i; // se guarda un puntero al siguiente Byte de datos
            i = i + 8;
            half_RawDataByte = (RawDataByte + 4) -8U >> 1; // dividide el byte entre 2.
            j = 0;
            while( j < half_RawDataByte ){
                byte_ptr = ptr_stage2 + ptrRawData + i; // se guarda un puntero al siguiente Byte de datos
                i = i + 2;
                if (byte_ptr >> 0xc != 0){ // desplazar 12 (0xc) bits equivale a dividir el valor de ptr2data por 2^12 (que es 4096).
                    newValue = var4 + RawDataByte + (byte_ptr & 0xfff)
                    aux_ptr = 0;
                    copy_memory(aux_ptr, newValue, 4);
                    aux_ptr = aux_ptr + var;
                    copy_memory(newValue, aux_ptr,4);
                }
                j = j + 1;
            }
        }

        ptr_import_table = ptr_stage2 + import_table
        ptr_ImportTable2 = ptr_import_table;
        if (ptr_import_table == 0) {
            ret_val = 0;
        } else {
            while(ptr_ImportTable +0xc != 0){ // ptr_ImportTable +0xc = Name of DLL. si el nombre de la dll actual es distinta de 0
                name = ptr_stage2 + ptr_ImportTable2 + 0xc;
                ret_val = fun74(name)
                var58 = ret_val;
                if (var58 == 0){
                    return 0;
                }
                FirstThunk = ptr_stage2 + ptr_ImportTable2 + 0x10; 
                while (FirstThunk != 0){
                    if (FirstThunk & 0x80000000 == 0) {// Si el resultado es 0, entonces FirstThunk contiene una dirección directa en la IAT para la función importada
                        vard4 = ptr_2stage2 + FirstThunk;
                        ret_val = fun5c(FirstThunk, vard4+2)
                        varc4 = ret_val;
                        FirstThunk = varc4;
                    } else {
                        varc0 = FirstThunk & 0xffff;
                        ret_val = func5(var58, varc0);
                        FirstThunk = ret_val;
                    }
                    FirstThunk = FirstThunk + 4;
                }
                ptr_ImportTable2 = ptr_ImportTable2 + 0x14; // FirstThunk
            }
            bVar1 = Funcion100121f0(ptr_stage2)

            if (CONCAT31(extraoutVar, bVar1) != 0){ // CONCAT31 concatena los bits de extraoutVar(3bits) y bVar1(1bit)
                TLSTable = ptr_stage2 + ptr_PEheader + 0xc0; // TLSTable
                AddressOfCallBacks = TLSTable + 0xc; // AddressOfCallBacks: RVA de una lista de punteros a funciones de callback
                while(AddressOfCallbacks != 0){
                    Callback = *AddressOfCallbacks;
                    Callback(ptr_stage2, 1, 0);
                    AddressOfCallbacks = AddressOfCallbacks +4;
                }
            }

            AddressOfEntryPoint = ptr_2stage2 + ptr_PEheaders + 0x28; // AddressOfEntryPoint
            ret_val = AddressOfEntryPoint(EBP+8, 1, 0); // ejecución del stage 2
            
            vare4 = ret_val;
            if (vare4 ==0){
                ret_vsl = 0;
            } else {
                ret_val = ptr_stage2;
            }
        }
    }
    return ret_val;
}