#include <stdio.h>
#include <stdbool.h>
#include <capstone/capstone.h>

#define CODE "\x55\x48\x8b\x05\xb8\x13\x00\x00"

extern "C" {


int main(void)
{
    csh handle;
    cs_insn* insn;
    size_t count;

    if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle)) {
        // printf("ERROR: Failed to initialize engine!\n");
        return 1;
    }

    count = cs_disasm(handle, (unsigned char*)CODE, sizeof(CODE) - 1, 0x1000, 0, &insn);
    if (count) {
        size_t j;
        char buffer[1024];
        for (j = 0; j < count; j++) {
            memset(buffer, 0, sizeof(buffer));
            intptr_t addr = insn[j].address;
            char * mnemonic = insn[j].mnemonic;
            char * op_str = insn[j].op_str;
            snprintf(buffer, 1024, "0x%lx: %s %s\n", addr, mnemonic, op_str);
            // printf("%s", insn[j].mnemonic);
            printf("%s", buffer);
        }
        cs_free(insn, count);
    }
    else
        // printf("ERROR: Failed to disassemble given code!\n");

    cs_close(&handle);

    return 0;
}

}