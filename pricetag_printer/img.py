import cv2


def floyd_steinberg_dither(img):
    '''Applies the Floyd-Steinberf dithering to img, in place.
    img is expected to be a 8-bit grayscale image.

    Algorithm borrowed from wikipedia.org/wiki/Floyd%E2%80%93Steinberg_dithering.
    '''
    h, w = img.shape

    def adjust_pixel(y, x, delta):
        if y < 0 or y >= h or x < 0 or x >= w:
            return
        img[y][x] = min(255, max(0, img[y][x] + delta))

    for y in range(h):
        for x in range(w):
            new_val = 255 if img[y][x] > 127 else 0
            err = img[y][x] - new_val
            img[y][x] = new_val
            adjust_pixel(y, x + 1, err * 7/16)
            adjust_pixel(y + 1, x - 1, err * 3/16)
            adjust_pixel(y + 1, x, err * 5/16)
            adjust_pixel(y + 1, x + 1, err * 1/16)


def read_img(
        filename,
        print_width,
        print_height,
        logger,
        img_binarization_algo,
        show_preview,
        invert):
    
    rotate = cv2.imread(filename,cv2.ROTATE_90_COUNTERCLOCKWISE )
    im = cv2.rotate(rotate, cv2.IMREAD_GRAYSCALE)
    height = im.shape[0]
    width = im.shape[1]
    
    #height = im.shape[0]
    #width = im.shape[1]

    factor = print_width / width
   # resized = cv2.resize(im, (int(width * factor), int(height *
     #                    factor)), interpolation=cv2.INTER_AREA)
    down_points = (print_width, print_height)
    resized = cv2.resize(im, down_points, interpolation= cv2.INTER_LINEAR)

    if img_binarization_algo == 'floyd-steinberg':
        logger.info(f'⏳ Applying Floyd-Steinberg dithering to image...')
        floyd_steinberg_dither(resized)
        logger.info(f'✅ Done.')
        threshold = 127
    elif img_binarization_algo == 'mean-threshold':
        threshold = resized.mean()
    else:
        logger.error(
            f'🛑 Unknown image binarization algorithm: {img_binarization_algo}')
        raise RuntimeError(
            f'unknown image binarization algorithm: {img_binarization_algo}')
    if invert:
        resized = resized <= threshold
    else:
        resized = resized > threshold

    if show_preview:
        # Convert from our boolean representation to float.
        preview_img = resized.astype(float)
        cv2.imshow('Preview', preview_img)
        logger.info('ℹ️  Displaying preview.')
        # Calling waitKey(1) tells OpenCV to process its GUI events and actually display our image.
        cv2.waitKey(1)
        if input(f'🤔 Go ahead with print? [Y/n]? ').lower() == 'n':
            logger.info('🛑 Aborted print.')
            return None

    return resized
