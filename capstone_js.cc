#include <stdio.h>
#include <stdbool.h>
#include <capstone/capstone.h>
#include <emscripten/emscripten.h>

extern "C" {

struct FunctionRemoveScope {
    void (*callback)(const char *, const char *);
    FunctionRemoveScope(void (*cb)(const char *, const char *)): callback(cb) {};
    ~FunctionRemoveScope() {
        EM_ASM_(Module.removeFunction($0), callback);
    }
};

EMSCRIPTEN_KEEPALIVE void disassemble(intptr_t start_addr, const uint8_t *code, intptr_t code_len, int arch , int mode, const char *js_callback)
{
    void (*callback)(const char *, const char *) = (void (*)(const char *, const char *))js_callback;
    auto scope = FunctionRemoveScope(callback);
    csh handle;
    cs_insn* insn;
    size_t count;

    if (cs_open((cs_arch)arch, (cs_mode)mode, &handle)) {
        callback(NULL, "ERROR: Failed to initialize engine!\n");
        return;
    }

    count = cs_disasm(handle, code, code_len, start_addr, 0, &insn);
    if (count) {
        size_t j;
        char buffer[1024] = {0};
        for (j = 0; j < count; j++) {
            memset(buffer, 0, sizeof(buffer));
            intptr_t addr = insn[j].address;
            char * mnemonic = insn[j].mnemonic;
            char * op_str = insn[j].op_str;
            snprintf(buffer, 1024, "0x%lx: %s %s\n", addr, mnemonic, op_str);
            // !!! Error code
            // snprintf(buffer, 1024, "0x%lx: %s %s\n", insn[j].address, insn[j].mnemonic, insn[j].op_str);
            callback(buffer, NULL);
        }
        cs_free(insn, count);
    }
    else
        callback(NULL, "ERROR: Failed to disassemble given code!\n");

    cs_close(&handle);

    return;
}

EMSCRIPTEN_KEEPALIVE int add(int a, int b)
{
    return a + b;
}
EMSCRIPTEN_KEEPALIVE int sub(int a, int b)
{
    return a - b;
}

}