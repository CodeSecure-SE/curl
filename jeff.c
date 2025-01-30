// The following is copied from GNU Chess 5.0.8
char *return_append_str(char *dest, const char *s) {
/* Append text s to dest, and return new result. */
        char *new_loc;
        size_t new_len;
        /* This doesn't have buffer overflow vulnerabilities, because
           we always allocate for enough space before appending. */
        if (!dest) {
                new_loc = (char *) malloc(strlen(s))+1;
                strcpy(new_loc, s);
                return new_loc;
        }
        new_len = strlen(dest) + strlen(s) + 1;
        new_loc = (char *) malloc(new_len);
        strcpy(new_loc, dest);
        if (!new_loc) return dest; /* Can't do it, throw away the data */
        strcat(new_loc, s);
        return new_loc;
}
